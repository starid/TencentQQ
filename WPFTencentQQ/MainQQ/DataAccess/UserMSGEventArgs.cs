using MainQQ.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainQQ.DataAccess
{
    public class UserMSGEventArgs : EventArgs
    {
        public UserMSGEventArgs(UserMsg _userMsg)
        {
            this.userMsg = _userMsg;
        }

        public UserMsg userMsg { get; private set; }
    }
}
