using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 短信猫
{
    public partial class Form8 : Form
    {
        public Form8()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 构造函数 传递参数
        /// </summary>
        /// <param name="msgCenter">短信中心</param>
        /// <param name="time">时间字符串</param>
        /// <param name="phone">手机号码</param>
        /// <param name="msg">短信内容</param>
        public Form8(string msgCenter,string time,string phone,string msg)
        {
            InitializeComponent();

            //
            textBox1.Text = msgCenter;
            textBox2.Text = time.Substring(0, 4) + "-" + time.Substring(4, 2) + "-" + time.Substring(6, 2) + " " +
                time.Substring(8, 2) + ":" + time.Substring(10, 2) + ":" + time.Substring(12);
            textBox3.Text = phone;
            textBox4.Text = msg;
        }

        private void Form8_Load(object sender, EventArgs e)
        {
            label6.Visible = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox5.Text == null || textBox5.Text.Length == 0)
            {
                MessageBox.Show("不允许发送空短信");
            }
            else if (textBox5.Text.Length > 70)
            {
                MessageBox.Show("短信字数过长");
            }
            else
            {
                label6.Visible = true;
                try
                {
                    Program.gm.SendMsg(textBox3.Text, textBox5.Text);
                }
                catch
                {
                    MessageBox.Show("发送失败");
                }
                label6.Visible = false;

                this.Close();
            }
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

            label7.Text = textBox5.Text.Length.ToString() + "/70";
            if (textBox5.Text.Length <= 70)
            {
                label7.ForeColor = Color.Green;
            }
            else
            {
                label7.ForeColor = Color.Red;
            }
        }
    }
}
