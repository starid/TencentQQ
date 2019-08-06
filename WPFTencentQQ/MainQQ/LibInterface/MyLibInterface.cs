using System.Runtime.InteropServices;
using System.Text;
using MainQQ.CallBack;

namespace MainQQ.LibInterface
{
    class MyLibInterface
    {
        #region NetLib输出函数
        [DllImport("..\\binD\\NetLib.dll", EntryPoint = "StartTheSystem", CallingConvention = CallingConvention.StdCall)]
        public static extern bool StartTheSystem(int m_iPortNr, uint m_iMaxNumberOfConnections, uint m_iNrOfIOWorkers,
            uint m_iNrOfLogicalWorkers, uint m_iMaxNrOfFreeBuff, uint m_iMaxNrOfFreeContext, bool m_iSendInOrder,
            bool m_bReadInOrder, uint m_iNrOfPendlingReads/*,CallBackFuctions.EKFNetLibCallback render*/);
        /// <summary>
        /// 连接服务器
        /// </summary>
        /// <param name="ip"></param>
        /// <param name="port"></param>
        /// <returns></returns>
        [DllImport("..\\binD\\NetLib.dll", EntryPoint = "OnConnectA", CallingConvention = CallingConvention.StdCall)]
        public static extern bool OnConnectA(SocketCallBackFuctions.EKFNetLibCallback render, char[] ip, short port, uint _inet);

        [DllImport("..\\binD\\NetLib.dll", EntryPoint = "OnDisconnect", CallingConvention = CallingConvention.StdCall)]
        public static extern void OnDisconnect(uint _socket);

        /// <summary>
        /// 终止IOCP
        /// </summary>
        /// <returns></returns>
        [DllImport("..\\binD\\NetLib.dll", EntryPoint = "EndTheSystem", CallingConvention = CallingConvention.StdCall)]
        public static extern bool EndTheSystem();

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="_type"></param>
        /// <param name="render"></param>
        [DllImport("..\\binD\\NetLib.dll", EntryPoint = "SendPacket", CallingConvention = CallingConvention.StdCall)]
        public static extern void SendPacket(uint type, byte[] msg,uint size);
        #endregion

        #region Packet输出函数
        [DllImport("..\\binD\\Packet.dll", EntryPoint = "PackPacket", CallingConvention = CallingConvention.StdCall)]
        public static extern void PackPacket(byte []bytes,uint _len, [MarshalAs(UnmanagedType.LPArray,SizeConst=1024)] ref byte [] msg,ref uint size);

        [DllImport("..\\binD\\Packet.dll", EntryPoint = "_InitId", CallingConvention = CallingConvention.StdCall)]
        public static extern void _InitId(uint _id);

        [DllImport("..\\binD\\Packet.dll", EntryPoint = "_InitPassword", CallingConvention = CallingConvention.StdCall)]
        public static extern void _InitPassword(byte []password,uint len);

        [DllImport("..\\binD\\Packet.dll", EntryPoint = "_InitServer", CallingConvention = CallingConvention.StdCall)]
        public static extern void _InitServer(uint _ip,uint _port,uint _nettype);

        [DllImport("..\\binD\\Packet.dll", EntryPoint = "unPackPacket", CallingConvention = CallingConvention.StdCall)]
        public static extern void unPackPacket(byte []msg,uint size,[MarshalAs(UnmanagedType.LPArray, SizeConst = 1024)] ref byte[] notifymsg, ref uint notifysize);
        #endregion

    }
}
