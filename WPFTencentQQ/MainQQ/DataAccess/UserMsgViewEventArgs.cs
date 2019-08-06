using MainQQ.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MainQQ.DataAccess
{
    public class UserMsgViewEventArgs : EventArgs
    {
        public UserMsgViewEventArgs(User _user, uint _bindType)
        {
            this._User = _user;
            _BindType = _bindType;
        }

        public uint _BindType { get; private set; }
        public User _User { get; private set; }
    }
}
