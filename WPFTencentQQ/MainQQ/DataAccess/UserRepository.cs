using MainQQ.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Linq;

namespace MainQQ.DataAccess
{
    /// <summary>
    /// Represents a source of Users in the application.
    /// </summary>
    public class UserRepository
    {
        #region Fields

        readonly List<User> _Users;

        protected IocpParam _IocpParam;

        #endregion // Fields

        #region Constructor

        /// <summary>
        /// Creates a new repository of Users.
        /// </summary>
        /// <param name="UserDataFile">The relative path to an XML resource file that contains User data.</param>
        public UserRepository(string UserDataFile)
        {
            _Users = LoadUsers(UserDataFile);
        }

        #endregion // Constructor

        #region Public Interface

        /// <summary>
        /// Raised when a User is placed into the repository.
        /// </summary>
        public event EventHandler<UserAddedEventArgs> UserAdded;

        /// <summary>
        /// Places the specified User into the repository.
        /// If the User is already in the repository, an
        /// exception is not thrown.
        /// </summary>
        public void AddUser(User User)
        {
            if (User == null)
                throw new ArgumentNullException("User");

            int index = _Users.FindIndex(x => x.Id == User.Id && x.Password == User.Password);
            if (index!=-1)
            {
                return;
            }

            if (!_Users.Contains(User))
            {
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load("Data\\users.xml");

                XmlNode root = xmlDoc.SelectSingleNode("users");
                XmlElement xe1 = xmlDoc.CreateElement("user");
                xe1.SetAttribute("id", User.Id);
                xe1.SetAttribute("uid", User.Id);
                xe1.SetAttribute("password", User.Password);
                if (User.IsLogin)
                    xe1.SetAttribute("isLogin", "true");
                else
                    xe1.SetAttribute("isLogin", "false");
                root.AppendChild(xe1);
                xmlDoc.Save("Data\\users.xml");  

                _Users.Add(User);

                if (this.UserAdded != null)
                    this.UserAdded(this, new UserAddedEventArgs(User));
            }
        }

        public event EventHandler<UserAddedEventArgs> UserDel;

        public void DelUser(User User)
        {
            if (User == null)
                throw new ArgumentNullException("User");

            if (_Users.Contains(User))
            {

                XmlDocument xdoc = new XmlDocument();
                xdoc.Load("Data\\users.xml");

                XmlNodeList xnodes = xdoc.SelectNodes("users/user[@id='" + User.Id + "' and @uid='" + User.Id + "'and @password='" + User.Password + "']");

                foreach (XmlNode node in xnodes)
                {
                    xdoc.DocumentElement.RemoveChild(node);
                }
                xdoc.Save("Data\\users.xml");

                List<User> users = _Users.FindAll(x => x.Id==User.Id&&x.Password==User.Password);
                foreach(User user in users)
                {
                    _Users.Remove(user);
                    if (this.UserDel != null)
                        this.UserDel(this, new UserAddedEventArgs(user));
                }
            }
        }

        /// <summary>
        /// Returns true if the specified User exists in the
        /// repository, or false if it is not.
        /// </summary>
        public bool ContainsUser(User User)
        {
            if (User == null)
                throw new ArgumentNullException("User");

            int index = _Users.FindIndex(x => x.Id == User.Id && x.Password == User.Password);
            if (index == -1)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Returns a shallow-copied list of all Users in the repository.
        /// </summary>
        public List<User> GetUsers()
        {
            return new List<User>(_Users);
        }

        public void SetIocpParam(IocpParam IocpParam)
        {
            if (IocpParam == null)
                throw new ArgumentNullException("IocpParam");
            this._IocpParam = IocpParam;
        }
        public IocpParam GetIocpParam()
        {
            if (_IocpParam == null)
                return IocpParam.CreateIocpParam();
            else
                return new IocpParam(_IocpParam);
        }

        #endregion // Public Interface

        #region Private Helpers

        static List<User> LoadUsers(string UserDataFile)
        {
            // In a real application, the data would come from an external source,
            // but for this demo let's keep things simple and use a resource file.
            using (Stream stream = GetResourceStream(UserDataFile))
            using (XmlReader xmlRdr = new XmlTextReader(stream))
                return
                    (from UserElem in XDocument.Load(xmlRdr).Element("users").Elements("user")
                     select User.CreateUser(
                        (string)UserElem.Attribute("id"),
                        (string)UserElem.Attribute("password"),
                        (bool)UserElem.Attribute("isLogin")
                         )).ToList();
        }

        static Stream GetResourceStream(string resourceFile)
        {
            Stream stream = File.Open(resourceFile, FileMode.OpenOrCreate);
            return stream;
        }

        #endregion // Private Helpers
    }
}