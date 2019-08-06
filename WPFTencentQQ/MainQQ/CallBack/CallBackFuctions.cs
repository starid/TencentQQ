using System.Text;
using System.Runtime.InteropServices;
using System;
using System.IO;

namespace MainQQ.CallBack
{
    class SocketCallBackFuctions
    {
        private Object thisObject = new Object();
        public uint _Socket = 0;
        public delegate void ViewModelNetDelegate(TransmitParameters.CallArgus m);
        public event ViewModelNetDelegate UserViewModelNetEvent;
        public EKFNetLibCallback mNetLibCallback;


        public delegate void EKFNetLibCallback(uint _socket, uint msgType, [MarshalAs(UnmanagedType.LPArray, SizeConst = 1000)]byte[] msg, uint bytes);
        public void NetLibMainCallback(uint _socket,uint msgType, [MarshalAs(UnmanagedType.LPArray,SizeConst=1000)]byte[] msg, uint bytes)
        {
            lock (thisObject)
            {
                switch (msgType)
                {
                    case 0x0000:
                        {
                            TransmitParameters.NetArgus mNetArgus = new TransmitParameters.NetArgus();
                            mNetArgus.type = msgType;
                            mNetArgus.socket = _socket;
                            TransmitParameters.CallArgus mCallArgus = new TransmitParameters.CallArgus(); ;
                            mCallArgus.isCallSucess = true;
                            mCallArgus.net_argu = mNetArgus;
                            UserViewModelNetEvent.BeginInvoke(mCallArgus, null, null);
                        } break;
                    case 0x0001:
                        {
                            TransmitParameters.NetArgus mNetArgus = new TransmitParameters.NetArgus();
                            mNetArgus.type = msgType;
                            mNetArgus.socket = _socket;
                            mNetArgus.send_recv_data = new byte[bytes];
                            Array.Copy(msg, mNetArgus.send_recv_data, bytes);
                            TransmitParameters.CallArgus mCallArgus = new TransmitParameters.CallArgus(); ;
                            mCallArgus.isCallSucess = true;
                            mCallArgus.net_argu = mNetArgus;
                            UserViewModelNetEvent.BeginInvoke(mCallArgus, null, null);
                        } break;
                    case 0x0002:
                        {
                            TransmitParameters.NetArgus mNetArgus = new TransmitParameters.NetArgus();
                            mNetArgus.type = msgType;
                            mNetArgus.socket = _socket;
                            mNetArgus.notify_msg = new byte[bytes];
                            Array.Copy(msg, mNetArgus.notify_msg, bytes);
                            TransmitParameters.CallArgus mCallArgus = new TransmitParameters.CallArgus(); ;
                            mCallArgus.isCallSucess = true;
                            mCallArgus.net_argu = mNetArgus;
                            UserViewModelNetEvent.BeginInvoke(mCallArgus, null, null);
                        } break;
                    default:
                        {
                            GlobalVar.ErrorMessage("error");
                        } break;
                }
            }
            return;
        }
        
    }
}
