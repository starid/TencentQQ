using System;
using System.ComponentModel;
using System.Windows.Input;
using MainQQ.DataAccess;
using MainQQ.Models;
using MainQQ.Properties;
using System.Net;
using MainQQ.LibInterface;
using MainQQ.CallBack;
using System.Collections.ObjectModel;
using System.IO;
using System.Windows.Threading;
using System.Windows;

namespace MainQQ.ViewModels
{
    /// <summary>
    /// A UI-friendly wrapper for a User object.
    /// </summary>
    public class UserViewModel : WorkspaceViewModel, IDataErrorInfo
    {
        #region Fields

        readonly User _User;
        readonly UserRepository _UserRepository;
        bool _isSelected;
        RelayCommand _loginCommand;
        RelayCommand _saveCommand;
        RelayCommand _logoutCommand;
        RelayCommand _viewRecvMsgCommand;
        RelayCommand _viewSendMsgCommand;
        RelayCommand _delUser;
        private Object thisLock = new Object();
        SocketCallBackFuctions mCallBackFuctions = new SocketCallBackFuctions();
        DispatcherTimer dispatcherTimer = new DispatcherTimer();
        public event EventHandler<EventArgs> CloseViewEvent;
        public event EventHandler<UserMsgViewEventArgs> MsgViewModelEvent;

        #endregion // Fields

        #region Constructor

        public UserViewModel(User User, UserRepository UserRepository)
        {
            if (User == null)
                throw new ArgumentNullException("User");

            if (UserRepository == null)
                throw new ArgumentNullException("UserRepository");

            _User = User;
            _UserRepository = UserRepository;

            InitNetTypeSource();
            InitOsType();
            InitLoginStateSource();

            mCallBackFuctions.mNetLibCallback = new SocketCallBackFuctions.EKFNetLibCallback(mCallBackFuctions.NetLibMainCallback);
            mCallBackFuctions.UserViewModelNetEvent+=NetEventResult;

            _User.MSGSync += OnMsgAddToRepository;

            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_heart_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 1, 0);//每隔一分钟执行一次
        }

        #endregion // Constructor

        #region User Properties

        public string Id
        {
            get { return _User.Id; }
            set
            {
                if (value == _User.Id)
                    return;

                _User.Id = value;

                base.OnPropertyChanged("Id");
            }
        }

        public bool IsLogin
        {
            get { return _User.IsLogin; }
        }

        public string Password
        {
            get { return _User.Password; }
            set
            {
                if (value == _User.Password)
                    return;

                _User.Password = value;

                base.OnPropertyChanged("Password");
            }
        }

        public bool IsAutoLogin
        {
            get { return _User.IsAutoLogin; }
            set
            {
                if (value == _User.IsAutoLogin)
                    return;

                _User.IsAutoLogin = value;

                base.OnPropertyChanged("IsAutoLogin");
            }
        }

        public bool IsRememberPwd
        {
            get { return _User.IsRememberPwd; }
            set
            {
                if (value == _User.IsRememberPwd)
                    return;

                _User.IsRememberPwd = value;

                base.OnPropertyChanged("IsRememberPwd");
            }
        }

        public NetType SelectNetType
        {
            get { return _User.SelectNetType; }
            set
            {
                if (value == _User.SelectNetType)
                    return;

                _User.SelectNetType = value;

                base.OnPropertyChanged("SelectNetType");
            }
        }

        public ObservableCollection<NetType> NetTypeSource
        {
            get;
            private set;
        }

        public OsType SelectOsType
        {
            get { return _User.SelectOsType; }
            set
            {
                if (value == _User.SelectOsType)
                    return;

                _User.SelectOsType = value;

                base.OnPropertyChanged("SelectOsType");
            }
        }
        public ObservableCollection<OsType> OsTypeSource { get; private set; }

        public ObservableCollection<UserMsg> GetAllMSG
        {
            get { return _User.SendorRecvMSG; }
            set { _User.SendorRecvMSG = value; }
        }

        public LoginState SelectLoginState
        {
            get {
                return _User.SelectLoginState; 
            }
            set
            {
                if (value == _User.SelectLoginState)
                    return;

                _User.SelectLoginState = value;

                base.OnPropertyChanged("SelectLoginState");
            }
        }

        public ObservableCollection<LoginState> LoginStateSource{get;private set;}

        #endregion // User Properties

        #region Presentation Properties

        public override string DisplayName
        {
            get
            {
                if (this.IsNewUser)
                {
                    return Resources.UserViewModel_DisplayName;
                }
                else if (_User.IsLogin)
                {
                    return _User.Id;
                }
                else
                {
                    return String.Format("{0}", _User.Id);
                }
            }
        }

        /// <summary>
        /// Gets/sets whether this User is selected in the UI.
        /// </summary>
        public bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                if (value == _isSelected)
                    return;

                _isSelected = value;

                base.OnPropertyChanged("IsSelected");
            }
        }

        /// <summary>
        /// Returns a command that saves the User.
        /// </summary>
        public ICommand LoginCommand
        {
            get
            {
                if (_loginCommand == null)
                {
                    _loginCommand = new RelayCommand(
                        param => this.Login(),
                        param => this.CanLogin
                        );
                }
                return _loginCommand;
            }
        }

        public ICommand SaveCommand
        {
            get
            {
                if (_saveCommand == null)
                {
                    _saveCommand = new RelayCommand(
                        param => this.Save(),
                        param => this.CanSave
                        );
                }
                return _saveCommand;
            }
        }

        public ICommand LogoutCommand
        {
            get
            {
                if (_logoutCommand == null)
                {
                    _logoutCommand = new RelayCommand(
                        param => this.Logout(),
                        param => this.CanLogout
                        );
                }
                return _logoutCommand;
            }
        }

        public ICommand ViewRecvMsg {
            get
            {
                if (_viewRecvMsgCommand == null)
                {
                    _viewRecvMsgCommand = new RelayCommand(
                        param => this.RecvMsgView(),
                        param => true
                        );
                }
                return _viewRecvMsgCommand;
            }
        }

        public ICommand ViewSendMsg
        {
            get
            {
                if (_viewSendMsgCommand == null)
                {
                    _viewSendMsgCommand = new RelayCommand(
                        param => this.SendMsgView(),
                        param => true
                        );
                }
                return _viewSendMsgCommand;
            }
        }

        public ICommand DelUserCommand
        {
            get
            {
                if (_delUser == null)
                {
                    _delUser = new RelayCommand(
                        param => this.DelUser(),
                        param => true
                        );
                }
                return _delUser;
            }
        }

        #endregion // Presentation Properties

        #region Public Methods
        public void InitNetTypeSource()
        {
            if (NetTypeSource==null)
            { 
                this.NetTypeSource = new ObservableCollection<NetType>() {
                 new NetType() { ID = 1, Code = 0x10, Info = "UDP" },
                 new NetType() { ID = 2, Code = 0x11, Info = "TCP" }};
            }
            this.SelectNetType = NetTypeSource[0];
        }

        public void InitOsType()
        {
            if (OsTypeSource == null)
            {
                this.OsTypeSource = new ObservableCollection<OsType>() {
                 new OsType() { ID = 1, Code = 0x20, Info = "Windows" },
                 new OsType() { ID = 2, Code = 0x21, Info = "Android" },
                 new OsType() { ID = 3, Code = 0x22, Info = "Ios" },
                };
            }
            this.SelectOsType = OsTypeSource[0];
        }

        public void InitLoginStateSource()
        {
            if(LoginStateSource==null)
            {
                this.LoginStateSource = new ObservableCollection<LoginState>(){
                 new LoginState() { ID = 1, Code = 0x20, Info = "我在线上" },
                 new LoginState() { ID = 2, Code = 0x21, Info = "Q我吧" },
                 new LoginState() { ID = 3, Code = 0x22, Info = "离开" },
                 new LoginState() { ID = 4, Code = 0x23, Info = "忙碌" },
                 new LoginState() { ID = 5, Code = 0x24, Info = "请勿打扰" },
                 new LoginState() { ID = 6, Code = 0x25, Info = "隐身" },
                };
            }
            this.SelectLoginState = LoginStateSource[0];
        }

        /// <summary>
        /// Saves the User to the repository.  This method is invoked by the SaveCommand.
        /// </summary>
        public void Login()
        {
            if (!_User.IsValid)
                throw new InvalidOperationException(Resources.UserViewModel_Exception_CannotSave);

            if (!this.IsLogin)
            {
                //连接网络
                IPAddress mIPAddress;
                if (IPAddress.TryParse(GlobalVar.mLocalConfig.strServerHost, out mIPAddress))
                {
                    //有效ip地址
                    GlobalVar.mLocalConfig.strServerIp = GlobalVar.mLocalConfig.strServerHost;
                }
                else
                {
                    IPHostEntry hostinfo = Dns.GetHostEntry(GlobalVar.mLocalConfig.strServerHost);
                    IPAddress[] aryIP = hostinfo.AddressList;
                    GlobalVar.mLocalConfig.strServerIp = aryIP[0].ToString();
                }
                uint ip = (uint)Config.LocalConfig.IpToInt(GlobalVar.mLocalConfig.strServerIp);
                MyLibInterface._InitServer(ip, (uint)(GlobalVar.mLocalConfig.iServerPort), 1);
                char[] strIp = new char[20];
                GlobalVar.mLocalConfig.strServerIp.CopyTo(0, strIp, 0, GlobalVar.mLocalConfig.strServerIp.Length);
                bool Ret = MyLibInterface.OnConnectA(mCallBackFuctions.mNetLibCallback, strIp, GlobalVar.mLocalConfig.iServerPort, 1);
                if(!Ret)
                {
                    System.Windows.MessageBox.Show("连接失败，请检查是否启动StartSystem");
                }
            }
        }

        public void Logout()
        {
            SendPacket(0x0062); 
            dispatcherTimer.Stop();

            _User.LogoutUser();
            base.OnPropertyChanged("IsLogin");

        }

        public void Save()
        {
            if (!_User.IsValid)
                throw new InvalidOperationException(Resources.UserViewModel_Exception_CannotSave);

            if (this.IsNewUser)
            {
                _UserRepository.AddUser(_User);
                base.OnPropertyChanged("DisplayName");
                CloseViewEvent(this,new EventArgs());
            }
            else
                MessageBox.Show("用户已存在");
        }

        public void DelUser()
        {
            if (!_User.IsValid)
                throw new InvalidOperationException(Resources.UserViewModel_Exception_CannotSave);

            _UserRepository.DelUser(_User);

        }

        public User GetUser
        {
            get { return _User; }
        }

        /// <summary>
        ///唯一委托 
        /// </summary>
        public void NetEventResult(TransmitParameters.CallArgus mCallArgu)
        {
            //登录成功
            lock (thisLock)
            {
                switch (mCallArgu.net_argu.type)
                {
                    case 0x0000:
                        {
                            //NotifyNewConnection
                            //服务器已连接
                            this.mCallBackFuctions._Socket = mCallArgu.net_argu.socket;
                            uint id = 0;
                            uint.TryParse(this.Id, out id);
                            MyLibInterface._InitId(id);
                            byte[] pwd = System.Text.Encoding.ASCII.GetBytes(Password);
                            MyLibInterface._InitPassword(pwd, (uint)pwd.Length);

                            TransmitParameters.Pack mPack = new TransmitParameters.Pack();
                            mPack.type = 0x0825;
                            TransmitParameters.PackArgus mPackArgus = new TransmitParameters.PackArgus();
                            mPackArgus.ispack = true;
                            mPackArgus.pack_data = mPack;
                            TransmitParameters.CallArgus mCallArgus=new TransmitParameters.CallArgus();
                            mCallArgus.pack_argu = mPackArgus;

                            SendPacket(0x0825);
                        }break;
                    case 0x0001:
                        {
                            byte[] msg = new byte[1024];
                            uint size = (uint)msg.Length;
                            MyLibInterface.unPackPacket(mCallArgu.net_argu.send_recv_data, (uint)mCallArgu.net_argu.send_recv_data.Length, ref msg, ref size);


                            MemoryStream ms = new MemoryStream();
                            ms.Write(msg, 0, (int)size);
                            ms.Position = 0;
                            TransmitParameters.CallArgus temp = ProtoBuf.Serializer.Deserialize<TransmitParameters.CallArgus>(ms);

                            PacketMessageHander(temp);
                        }break;
                    case 0x0002:
                        {
                            //NotifyDisconnectedClient
                            //重新开始登陆
                            mCallBackFuctions._Socket = 0;
                            dispatcherTimer.Stop();
                            _User.LogoutUser();
                            base.OnPropertyChanged("IsLogin");
                            //System.Windows.MessageBox.Show("终结socket");

                        }break;
                }
            }
            return;
        }

        private delegate void AddAStudentEvent(UserMsg si);
        private void AddAStudent(UserMsg si)
        {
            _User.SyncMSG(_User, si);
        }
        public void PacketMessageHander(TransmitParameters.CallArgus mCallArgu)
        {
            if (!mCallArgu.isCallSucess)
            {
                return;
            }

            System.Threading.ThreadPool.QueueUserWorkItem(delegate
            {
                UserMsg userMsg = new UserMsg();
                userMsg.isSend = false;
                userMsg.cTime = DateTime.Now.ToString("HH:mm:ss");
                userMsg.Code = mCallArgu.pack_argu.unpack_data.type;
                userMsg.Msg = mCallArgu.pack_argu.unpack_data.data;
                Application.Current.Dispatcher.Invoke(new AddAStudentEvent(this.AddAStudent), userMsg);
            });

            switch (mCallArgu.pack_argu.unpack_data.type)
            {
                case 0x0825:
                    {
                        if (mCallArgu.pack_argu.unpack_data.isTurnIp)
                        {
                            //需要中转IP
                            MyLibInterface.OnDisconnect(mCallBackFuctions._Socket);

                            GlobalVar.mLocalConfig.strServerIp = Config.LocalConfig.IntToIp(mCallArgu.pack_argu.unpack_data.serverip);

                            uint ip = (uint)Config.LocalConfig.IpToInt(GlobalVar.mLocalConfig.strServerIp);
                            MyLibInterface._InitServer(ip, (uint)(GlobalVar.mLocalConfig.iServerPort), 1);
                            char[] strIp = new char[20];
                            GlobalVar.mLocalConfig.strServerIp.CopyTo(0, strIp, 0, GlobalVar.mLocalConfig.strServerIp.Length);
                            MyLibInterface.OnConnectA(mCallBackFuctions.mNetLibCallback,strIp, GlobalVar.mLocalConfig.iServerPort, 1);

                        }
                        else
                        {
                            SendPacket(0x0836);
                        }
                    } break;
                case 0x0836:
                    {
                        if (!mCallArgu.pack_argu.unpack_data.is0836Suc)
                        {
                            if (mCallArgu.loginresult.notifyMsg == "NEED_LOGINVERIFYAGAIN")
                            {
                                SendPacket(0x0836);
                                break;
                            }
                            else
                            {
                                System.Windows.MessageBox.Show(mCallArgu.loginresult.notifyMsg);
                                return;
                            }

                        }
                        else
                        {
                            SendPacket(0x0828);
                        }

                    } break;
                case 0x0828:
                    {
                        if (!mCallArgu.pack_argu.unpack_data.is0828Suc)
                        {
                            System.Windows.MessageBox.Show(mCallArgu.loginresult.notifyMsg);
                            return;
                        }
                        else
                        {
                            TransmitParameters.ToPackArgu toPackArgu=new TransmitParameters.ToPackArgu();
                            toPackArgu.type = 0x001D;
                            toPackArgu.msg = new byte[] { 0x34 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x12 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x26 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.type = 0x01BB;
                            toPackArgu.msg = new byte[] { 0x01,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  };
                            SendPacket(0x01BB, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x03, 0x00, 0x01, 0x00, 0x00 };
                            SendPacket(0x01BB, toPackArgu);
                            //SendPacket(0x0422);
                            SendPacket(0x0134);
                            //发送00EC导致下线
                            SendPacket(0x00EC);
                            SendPacket(0x00D1);
                            toPackArgu.type = 0x001D;
                            toPackArgu.msg = new byte[] { 0x20 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x21 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x22 };
                            SendPacket(0x001D, toPackArgu);
                            toPackArgu.msg = new byte[] { 0x31 };
                            SendPacket(0x001D, toPackArgu);
                            SendPacket(0x0001);
                        }
                    }break;
                case 0x00EC:
                {
                    _User.LoginUser();
                    base.OnPropertyChanged("IsLogin");
                    System.Windows.MessageBox.Show("登陆成功");
                    dispatcherTimer.Start();
                }break;
                case 0x0017:
                {
                    TransmitParameters.ToPackArgu toPackArgu = new TransmitParameters.ToPackArgu();
                    toPackArgu.type = 0x0017;
                    toPackArgu.msg = new byte[0x10];
                    toPackArgu.seq = mCallArgu.pack_argu.unpack_data.seq;
                    Array.Copy(mCallArgu.pack_argu.unpack_data.data, toPackArgu.msg, 0x10);
                    SendPacket(0x0017, toPackArgu);
                }break;
                default:
                    {
                        //消息
                    }break;
            }
        }

        public void SendPacket(ushort packet_type,TransmitParameters.ToPackArgu toPackArgu=null)
        {
            TransmitParameters.CallArgus mCallArgus1 = new TransmitParameters.CallArgus();
            mCallArgus1.pack_argu = new TransmitParameters.PackArgus();
            mCallArgus1.pack_argu.toPackArgu = new TransmitParameters.ToPackArgu();
            if (toPackArgu==null)
            {
                mCallArgus1.pack_argu.toPackArgu = new TransmitParameters.ToPackArgu();
            }else
                mCallArgus1.pack_argu.toPackArgu = toPackArgu;
            mCallArgus1.pack_argu.toPackArgu.type = packet_type;
            MemoryStream ms1 = new MemoryStream();
            ProtoBuf.Serializer.Serialize(ms1, mCallArgus1);

            byte[] msg = new byte[1024];
            uint size = (uint)msg.Length;
            MyLibInterface.PackPacket(ms1.ToArray(), (uint)ms1.Length, ref msg, ref size);

            MemoryStream ms2 = new MemoryStream();
            ms2.Write(msg, 0, (int)size);
            ms2.Position = 0;
            TransmitParameters.CallArgus mCallArgus = ProtoBuf.Serializer.Deserialize<TransmitParameters.CallArgus>(ms2);
            MyLibInterface.SendPacket(mCallBackFuctions._Socket, mCallArgus.pack_argu.pack_data.msg, (uint)mCallArgus.pack_argu.pack_data.msg.Length);

            System.Threading.ThreadPool.QueueUserWorkItem(delegate
            {
                UserMsg userMsg = new UserMsg();
                userMsg.isSend = true;
                userMsg.cTime = DateTime.Now.ToString("HH:mm:ss");
                userMsg.Code = packet_type;
                userMsg.Msg = mCallArgus.pack_argu.pack_data.msg;
                Application.Current.Dispatcher.Invoke(new AddAStudentEvent(this.AddAStudent), userMsg);
            });

        }

        public void RecvMsgView()
        {
            MsgViewModelEvent(_User, new UserMsgViewEventArgs(_User, 1));
        }

        public void SendMsgView()
        {
            MsgViewModelEvent(_User, new UserMsgViewEventArgs(_User,0));
        }

        #endregion // Public Methods

        #region Private Helpers

        /// <summary>
        /// Returns true if this User was created by the user and it has not yet
        /// been saved to the User repository.
        /// </summary>
        bool IsNewUser
        {
            get { return !_UserRepository.ContainsUser(_User); }
        }

        /// <summary>
        /// Returns true if the User is valid and can be saved.
        /// </summary>
        bool CanLogin
        {
            get { return _User.IsValid; }
        }

        bool CanSave
        {
            get { return _User.IsValid; }
        }

        bool CanLogout
        {
            get { return _User.IsLogin; }
        }

        private void dispatcherTimer_heart_Tick(object sender, EventArgs e)
        {
            SendPacket(0x0058);
        }

        #endregion // Private Helpers

        #region  Base Class Overrides
        protected override void OnDispose()
        {
            mCallBackFuctions.UserViewModelNetEvent -= this.NetEventResult;
            _User.MSGSync -= OnMsgAddToRepository;
            if (CloseViewEvent != null)
            { 
                Delegate[] dels = CloseViewEvent.GetInvocationList();
                foreach (Delegate d in dels)
                {
                    object delObj = d.GetType().GetProperty("Method").GetValue(d, null);
                    string funcName = (string)delObj.GetType().GetProperty("Name").GetValue(delObj, null);
                    CloseViewEvent -= d as EventHandler<EventArgs>;
                }
            }
            if(MsgViewModelEvent!=null)
            {
                Delegate[] dels = MsgViewModelEvent.GetInvocationList();
                foreach (Delegate d in dels)
                {
                    object delObj = d.GetType().GetProperty("Method").GetValue(d, null);
                    string funcName = (string)delObj.GetType().GetProperty("Name").GetValue(delObj, null);
                    MsgViewModelEvent -= d as EventHandler<UserMsgViewEventArgs>;
                }
            }
        }

        #endregion // Base Class Overrides

        #region Event Handling Methods
        void OnMsgAddToRepository(object sender, UserMSGEventArgs e)
        {
            base.OnPropertyChanged("GetAllMSG");
        }

        #endregion // Event Handling Methods

        #region IDataErrorInfo Members

        string IDataErrorInfo.Error
        {
            get { return (_User as IDataErrorInfo).Error; }
        }

        string IDataErrorInfo.this[string propertyName]
        {
            get
            {
                string error = null;
                error = (_User as IDataErrorInfo)[propertyName];

                // Dirty the commands registered with CommandManager,
                // such as our Save command, so that they are queried
                // to see if they can execute now.
                CommandManager.InvalidateRequerySuggested();

                return error;
            }
        }

        #endregion // IDataErrorInfo Members
    }
}