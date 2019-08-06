using System.Windows;
using System.Windows.Controls;

namespace MainQQ
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Initialize();
        }
        /// <summary>
        /// 初始化
        /// </summary>
        private void Initialize()
        {
            this.Title = "MainQQ";
            this.ResizeMode = ResizeMode.CanResizeWithGrip;
            this.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            this.Height = 500;
            this.Width = 800;
            //加载配置
            //udp
            GlobalVar.mLocalConfig.strServerHost = "sz.tencent.com";
            GlobalVar.mLocalConfig.iServerPort = 8000;
            //tcp
            //GlobalVar.mLocalConfig.strServerHost = "183.232.94.216";
            //GlobalVar.mLocalConfig.iServerPort = 443;
            //GlobalVar.mLocalConfig.strServerHost = "172.16.10.3";
            //GlobalVar.mLocalConfig.iServerPort = 999;
        }

    }
}
