using MainQQ.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;

namespace MainQQ.Common
{
    namespace ValueConverter
    {
        public class OppConverter : IValueConverter
        {
            object IValueConverter.Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                return !(bool)value;
            }
            object IValueConverter.ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public class MSGGetSendNumConverter : IValueConverter
        {
            object IValueConverter.Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                if (value == null)
                    return 0;
                else
                {
                    System.Collections.ObjectModel.ObservableCollection<UserMsg> Msgs = value as System.Collections.ObjectModel.ObservableCollection<UserMsg>;
                    return Msgs.Sum(msg => msg.isSend ? 1 : 0);
                }
            }
            object IValueConverter.ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public class MSGGetRecvNumConverter : IValueConverter
        {
            object IValueConverter.Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                if (value == null)
                    return 0;
                else
                {
                    System.Collections.ObjectModel.ObservableCollection<UserMsg> Msgs = value as System.Collections.ObjectModel.ObservableCollection<UserMsg>;
                    return Msgs.Sum(msg => msg.isSend ? 0 : 1);
                }
            }
            object IValueConverter.ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public class GetMSGsConverter : IMultiValueConverter
        {
            public object Convert(object []value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                if (value[0] == System.Windows.DependencyProperty.UnsetValue)
                    return 0;
                else
                {
                    System.Collections.ObjectModel.ObservableCollection<UserMsg> Msgs = value[0] as System.Collections.ObjectModel.ObservableCollection<UserMsg>;
                    if (Msgs == null) return null;
                    
                    uint type = (uint)value[1];
                    if (type == 0)
                    {
                        return Msgs.Where(msg => msg.isSend == true);
                    }else if(type==1)
                    {
                        return Msgs.Where(msg => msg.isSend == false);
                    }
                    return Msgs.Where(msg => msg.isSend == true);
                }
            }
            public object []ConvertBack(object value, Type []targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public class PacketTypeToHexStringConverter : IValueConverter
        {
            object IValueConverter.Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                if (value == null)
                    return 0;
                else
                {
                    uint code = (uint)value;
                    if (code == 0) return "0x0000";
                    return String.Format("0x{0:X4}", code);
                }
            }
            object IValueConverter.ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

        public class PasswordToStarConverter : IMultiValueConverter
        {
            public object Convert(object[] value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                if (value[0] == System.Windows.DependencyProperty.UnsetValue)
                    return 0;
                else
                {
                    string password = value[0] as string;
                    bool ishide = (bool)value[1];
                    if (password == null) return null;

                    if (ishide)
                    {
                        string newPassword = password.Substring(0, 1) + "*".PadLeft(password.Length - 2, '*') + password.Substring(password.Length - 1, 1);
                        return newPassword;
                    }
                    return password;
                }
            }
            public object[] ConvertBack(object value, Type[] targetType, object parameter, System.Globalization.CultureInfo culture)
            {
                throw new NotImplementedException();
            }
        }

    }

}
