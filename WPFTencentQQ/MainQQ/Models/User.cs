using MainQQ.DataAccess;
using MainQQ.Properties;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace MainQQ.Models
{
    public class User : IDataErrorInfo
    {
        #region Creation

        public static User CreateNewUser()
        {
            return new User();
        }

        public static User CreateUser(
            string id,
            string password,
            bool islogin)
        {
            return new User
            {
                Id = id,
                Password = password,
                IsLogin = islogin,
            };
        }

        protected User()
        {
        }

        #endregion // Creation

        #region State Properties
        /// <summary>
        /// 用户登录id（QQ号码，手机号码，邮箱）
        /// </summary>
        public string Id {get;set;}
        /// <summary>
        /// 密码
        /// </summary>
        public string Password{get;set;}
        /// <summary>
        /// 是否登录
        /// </summary>
        public bool IsLogin { get; set; }

        public bool IsAutoLogin { get; set; }

        public bool IsRememberPwd { get; set; }

        public NetType SelectNetType { get; set; }

        public OsType SelectOsType { get; set; }

        public ObservableCollection<UserMsg> SendorRecvMSG { get; set; }

        public LoginState SelectLoginState { get; set; }

        #endregion

        #region Base Class Overrides

  
        #endregion

        #region Public Interface

        public event EventHandler<UserMSGEventArgs> MSGSync;

        public void SyncMSG(User _user, UserMsg Msg)
        {
            if (this.SendorRecvMSG == null)
            {
                this.SendorRecvMSG = new ObservableCollection<UserMsg>(); 
            }
            this.SendorRecvMSG.Add(Msg);

            if (this.MSGSync != null)
                this.MSGSync(this, new UserMSGEventArgs(Msg));
        }

        public event EventHandler<EventArgs> UserLogin;

        public void LoginUser()
        {
            this.IsLogin = true;
            if (this.UserLogin != null)
                UserLogin(this, new EventArgs());
        }

        public event EventHandler<EventArgs> UserLogout;
        public void LogoutUser()
        {
            this.IsLogin = false;
            if (this.UserLogout != null)
                UserLogout(this, new EventArgs());
        }

        #endregion

        #region IDataErrorInfo Members

        string IDataErrorInfo.Error { get { return null; } }

        string IDataErrorInfo.this[string propertyName]
        {
            get { return this.GetValidationError(propertyName); }
        }

        #endregion // IDataErrorInfo Members

        #region Validation

        /// <summary>
        /// Returns true if this object has no validation errors.
        /// </summary>
        public bool IsValid
        {
            get
            {
                foreach (string property in ValidatedProperties)
                    if (GetValidationError(property) != null)
                        return false;

                return true;
            }
        }

        static readonly string[] ValidatedProperties = 
        { 
            "Id",
            "Password",
        };

        string GetValidationError(string propertyName)
        {
            if (Array.IndexOf(ValidatedProperties, propertyName) < 0)
                return null;

            string error = null;

            switch (propertyName)
            {
                case "Id":
                    error = this.ValidateId();//邮箱，手机号码
                    break;
                case "Password":
                    error = this.ValidatePassword();
                    break;

                default:
                    Debug.Fail("Unexpected property being validated on Customer: " + propertyName);
                    break;
            }

            return error;
        }

        string ValidateId()
        {
            if (IsValidQQ(this.Id) || IsValidPhoneNumber(this.Id) || IsValidEmailAddress(this.Id))
            {
                return null;
            }
            return MainQQ.Properties.Resources.User_Error_Id;
        }
        string ValidateEmail()
        {
            if (IsStringMissing(this.Id))
            {
                return Resources.User_Error_MissingEmail;
            }
            else if (!IsValidEmailAddress(this.Id))
            {
                return Resources.User_Error_InvalidEmail;
            }
            return null;
        }

        string ValidatePassword()
        {
            if (IsStringMissing(this.Password))
            {
                return MainQQ.Properties.Resources.Error_Default;
            }
            return null;
        }

        static bool IsStringMissing(string value)
        {
            return
                String.IsNullOrEmpty(value) ||
                value.Trim() == String.Empty;
        }

        static bool IsValidEmailAddress(string email)
        {
            if (IsStringMissing(email))
                return false;

            // This regex pattern came from: http://haacked.com/archive/2007/08/21/i-knew-how-to-validate-an-email-address-until-i.aspx
            string pattern = @"^(?!\.)(""([^""\r\\]|\\[""\r\\])*""|([-a-z0-9!#$%&'*+/=?^_`{|}~]|(?<!\.)\.)*)(?<!\.)@[a-z0-9][\w\.-]*[a-z0-9]\.[a-z][a-z\.]*[a-z]$";

            return Regex.IsMatch(email, pattern, RegexOptions.IgnoreCase);
        }

        static bool IsValidPhoneNumber(string phone)
        {
            if (IsStringMissing(phone))
                return false;
            string pattern = @"^1[3,4,5,7,8]\d{9}$";
            return Regex.IsMatch(phone, pattern, RegexOptions.IgnoreCase);
        }

        static bool IsValidQQ(string qq)
        {
            if (IsStringMissing(qq))
                return false;
            string pattern = @"^\d{5,10}$";
            return Regex.IsMatch(qq, pattern, RegexOptions.IgnoreCase);
        }
        #endregion // Validation
    }
}
