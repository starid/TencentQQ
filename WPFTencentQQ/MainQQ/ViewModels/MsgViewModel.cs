using MainQQ.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace MainQQ.ViewModels
{
    class MsgViewModel: WorkspaceViewModel
    {
        #region Fields
        User _User;
        RelayCommand _seleteItemCommand;
        #endregion // Fields

        #region Constructor

        public MsgViewModel(User user, uint _BindType)
        {
            //if (user.SendorRecvMSG == null)
            //{
            //    user.SendorRecvMSG = new ObservableCollection<UserMsg>();
            //    UserMsg m = new UserMsg();
            //    m.isSend = true;
            //    m.cTime = DateTime.Now.ToString();
            //    m.Code = 0x004F;
            //    m.Msg = new byte[] { 0x12, 0134, 0x45 };
            //    user.SendorRecvMSG.Add(m);
            //    UserMsg m1 = new UserMsg();
            //    m1.isSend = false;
            //    m1.cTime = DateTime.Now.ToString();
            //    m1.Code = 0x004F;
            //    m1.Msg = new byte[] { 
            //    0x16, 0x24, 0x25, 0x2c, 0x3c, 0xb3, 0x42, 0x96
            //    };
            //    user.SendorRecvMSG.Add(m1);
            //}
            _User = user;
            BindType = _BindType;
        }

        #endregion // Constructor

        #region User Properties
        public string Id
        {
            get { return _User.Id; }
        }

        public uint BindType { get; private set; }

        public ObservableCollection<UserMsg> AllMSG
        {
            get {return _User.SendorRecvMSG; }
        }

        public string HexContent
        {
            get;
            private set;
        }
        #endregion // User Properties


        #region Presentation Properties
        public override string DisplayName
        {
            get
            {
                //return String.Format("User:{0}", _User.Id);
                return "消息列表";
            }
        }

        public ICommand SelectItemChangedCommand
        {
            get
            {
                if (_seleteItemCommand == null)
                {
                    _seleteItemCommand = new RelayCommand(new Action<object>(SetHexView)
                        , param=>true);
                    //_seleteItemCommand = new RelayCommand(
                    //    param => this.SetHexView(),
                    //    param => true
                    //    );
                }
                return _seleteItemCommand;
            }
        }

        #endregion // Presentation Properties


        #region Public Methods

        public void SetHexView(object obj)
        {
            if(obj!=null)
            {
                UserMsg m = obj as UserMsg;
                string strHex = "";

                int sub = m.Msg.Length % 16;

                for (int i = 0; i < m.Msg.Length;i++)
                {
                   strHex += String.Format("{0:X2} ", m.Msg[i]);
                   if ((i+1) % 16 == 0)
                   {
                       for (int j = 0; j < 0x10;j++ )
                       {
                           char c = (char)(m.Msg[i - 15 + j]);
                           if(c>=32&&c<=126)
                               strHex += c;
                           else
                               strHex += '.';
                       }
                           strHex += '\n';
                   }
                }
                if(sub!=0)
                {
                    //最后一行字符
                    int len = 16 - sub;
                    for(int i=0;i<len;i++)
                    {
                        strHex += ' ';
                        strHex += ' ';
                        strHex += ' ';
                    }
                    for(int i=0;i<sub;i++)
                    {
                        char c = (char)(m.Msg[m.Msg.Length - sub + i]);
                        if (c >= 32 && c <= 126)
                            strHex += c;
                        else
                            strHex += '.';
                    }
                }
                HexContent = strHex;
                
                base.OnPropertyChanged("HexContent");
            }
        }

        #endregion // Public Methods

    }
}
