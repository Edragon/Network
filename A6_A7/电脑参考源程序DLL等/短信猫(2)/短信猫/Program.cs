using System;
using System.Collections.Generic;
using System.Windows.Forms;
using GSMMODEM;

namespace 短信猫
{
    static class Program
    {
        public static GSMModem gm = new GSMModem();         //设备类，全局变量，方便不同窗体使用

        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
