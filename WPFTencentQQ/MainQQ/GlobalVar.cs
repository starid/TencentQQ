using System.Windows;

namespace MainQQ
{
    class GlobalVar
    {
        public static Config.LocalConfig mLocalConfig = new Config.LocalConfig();

        /// <summary>
        /// 错误提示框
        /// </summary>
        /// <param name="strMessage"></param>
        public static void ErrorMessage(string strMessage)
        {
            MessageBox.Show(strMessage);
        }
    }
}
