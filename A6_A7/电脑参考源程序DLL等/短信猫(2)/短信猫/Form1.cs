using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 短信猫
{
    public partial class Form1 : Form
    {
        public Form2 f2;
        Form3 f3;
        Form4 f4;
        Form5 f5;
        Form6 f6;
        Form7 f7;

        public Form1()
        {
            InitializeComponent();

            //菜单窗体
            f2 = new Form2();
            f2.TopLevel = false;
            f2.FormBorderStyle = FormBorderStyle.None;
            f2.Parent = this.splitContainer1.Panel1;
            f2.Show();
            f2.F2Event += new Form2.F2EventHandler(f2_F2Event);         //绑定Form2事件

            //首页窗体
            f3 = new Form3();
            f3.TopLevel = false;
            f3.FormBorderStyle = FormBorderStyle.None;
            f3.Parent = this.splitContainer1.Panel2;
            f3.Show();
            f3.BringToFront();

            //发送短信窗体
            f4 = new Form4();
            f4.TopLevel = false;
            f4.FormBorderStyle = FormBorderStyle.None;
            f4.Parent = this.splitContainer1.Panel2;
            f4.Show();

            //读取短信窗体
            f5 = new Form5();
            f5.TopLevel = false;
            f5.FormBorderStyle = FormBorderStyle.None;
            f5.Parent = this.splitContainer1.Panel2;
            f5.Show();

            //设备管理窗体
            f6 = new Form6();
            f6.TopLevel = false;
            f6.FormBorderStyle = FormBorderStyle.None;
            f6.Parent = this.splitContainer1.Panel2;
            f6.Show();

            //帮助窗体
            f7 = new Form7();
            f7.TopLevel = false;
            f7.FormBorderStyle = FormBorderStyle.None;
            f7.Parent = this.splitContainer1.Panel2;
            f7.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        void f2_F2Event(object sender, GSMEventArgs e)
        {
            switch (e.Message)
            {
                case "首页":
                    f3.BringToFront();          //首页窗体移至最前
                    break;

                case "发送短信":
                    f4.BringToFront();          //发送短信窗体移至最前
                    break;

                case "读取短信":
                    f5.BringToFront();          //读取短信窗体移至最前
                    break;

                case "设备管理":
                    f6.BringToFront();          //设备管理窗体移至最前
                    break;

                case "帮助":
                    f7.BringToFront();          //帮助窗体移至最前
                    break;

                default: break;

            }
        }
    }

    //
    public class GSMEventArgs : EventArgs
    {
        /// <summary>
        /// 构造函数
        /// </summary>
        public GSMEventArgs()
        {

        }

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="message"></param>
        public GSMEventArgs(string message)
        {
            Message = message;
        }

        public string Message;
    }

}
