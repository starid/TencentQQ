using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainQQ.Models
{
    public class UserMsg
    {
        public bool isSend { set; get; }

        public string cTime { set; get; }
        public uint Code { set; get; }
        public byte[] Msg { set; get; }
    }
}
