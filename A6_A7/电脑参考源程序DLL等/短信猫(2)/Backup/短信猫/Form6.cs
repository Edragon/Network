using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace 短信猫
{
    public partial class Form6 : Form
    {
            //委托 事件 通知其他窗体，设备打开
        public delegate void GSMOpenHandler(object sender, GSMEventArgs ge);

        public event GSMOpenHandler GSMOpen = null;

        public Form6()
        {
            InitializeComponent();
            
            //初始化控件comboBox1
            foreach (string s in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(s);
            }
            if (comboBox1.Items.Count > 0)
            {
                //comboBox1.SelectedIndex = 0;
            }
            else
            {
                label3.Text = "未检测到串口";
            }

            //初始化控件comboBox2
            //comboBox2.SelectedIndex = 0;
        }

        private void Form6_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedText = Properties.Settings.Default.ComPort;               //读取设置

            comboBox2.SelectedText = Properties.Settings.Default.BaudRate;

            checkBox1.Checked = Properties.Settings.Default.AutoOpen;

            //设备属性初始化
            Program.gm.ComPort = Properties.Settings.Default.ComPort;
            Program.gm.BaudRate = Convert.ToInt32(Properties.Settings.Default.BaudRate);
            Program.gm.AutoDelMsg = true;

            if (Properties.Settings.Default.AutoOpen)                                   //根据设置决定是否打开设备
            {
                button1_Click(sender, e);                                               //调用button1的事件，完成设备的打开
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Program.gm.IsOpen == false)
            {
                try
                {
                    Program.gm.Open();
                    label3.Text = "打开成功";                       //改变状态指示
                    label3.ForeColor = Color.Green;

                    button1.Text = "关闭设备";

                    //新线程 事件引发
                    Thread thread = new Thread(GSMOpened);
                    thread.Start();
                }
                catch
                {
                    label3.Text = "打开失败";                       //改变状态指示
                    label3.ForeColor = Color.Red;
                } 
            }
            else
            {
                try
                {
                    Program.gm.Close();
                    label3.Text = "关闭成功";                       //改变状态指示
                    label3.ForeColor = Color.Red;

                    button1.Text = "打开设备";
                }
                catch
                {
                    label3.Text = "关闭失败";                       //改变状态指示
                    label3.ForeColor = Color.Yellow;
                }
            } 
        }

        //新线程函数 事件引发执行
        private void GSMOpened()
        {
            if (GSMOpen != null)
            {
                GSMOpen(this, new GSMEventArgs("设备成功打开"));
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            Properties.Settings.Default.AutoOpen = checkBox1.Checked;                   //更改设置文件

            Properties.Settings.Default.Save();                                         //保存设置文件
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Program.gm.IsOpen)
            {
                label3.Text = "设备打开时无法更改";
                label3.ForeColor = Color.Red;
            }
            else
            {
                Program.gm.ComPort = comboBox1.SelectedItem.ToString();     //设备属性改变
            }

            Properties.Settings.Default.ComPort = comboBox1.SelectedItem.ToString();                   //更改设置文件

            Properties.Settings.Default.Save();                                         //保存设置文件
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Program.gm.BaudRate = Convert.ToInt32(comboBox2.SelectedItem.ToString());   //设备属性改变

            Properties.Settings.Default.BaudRate = comboBox2.SelectedItem.ToString();                   //更改设置文件

            Properties.Settings.Default.Save();                                         //保存设置文件
        }
    }
}
