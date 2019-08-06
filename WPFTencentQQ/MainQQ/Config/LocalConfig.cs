using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainQQ.Config
{
    enum NetType
    {
        NET_UDP,
        NET_TCP
    }
    class LocalConfig
    {
        /// <summary>
        /// 网络协议类型
        /// </summary>
        public NetType net_type = NetType.NET_UDP;
        /// <summary>
        /// 手机硬件环境
        /// </summary>
        Hardware mHardware=new Hardware();
        
        //服务器地址
        public string strServerHost = null;
        public string strServerIp = null;
        public short iServerPort = 0;
        /// <summary>
        /// 构造函数
        /// </summary>
        public LocalConfig()
        {
        }

        /// <summary>
        /// IP地址与整数之间的转换
        /// </summary>
        public static long IpToInt(string ip)
        {
            char[] separator = new char[] { '.' };
            string[] items = ip.Split(separator);
            return long.Parse(items[0]) << 24
                    | long.Parse(items[1]) << 16
                    | long.Parse(items[2]) << 8
                    | long.Parse(items[3]);
        }

        /// <summary>
        /// 整数与IP地址之间的转换
        /// </summary>
        public static string IntToIp(long ipInt)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append((ipInt >> 24) & 0xFF).Append(".");
            sb.Append((ipInt >> 16) & 0xFF).Append(".");
            sb.Append((ipInt >> 8) & 0xFF).Append(".");
            sb.Append(ipInt & 0xFF);
            return sb.ToString();
        }
    }

}
