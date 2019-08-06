using MainQQ.Models;
using System;

namespace MainQQ.DataAccess
{
    /// <summary>
    /// Event arguments used by CustomerRepository's CustomerAdded event.
    /// </summary>
    public class UserAddedEventArgs : EventArgs
    {
        public UserAddedEventArgs(User newUser)
        {
            this.NewUser = newUser;
        }

        public User NewUser { get; private set; }
    }
}