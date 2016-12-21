using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace 短信猫
{
    public partial class Form9 : Form
    {
        //委托
        public delegate void AddNumEventHandler(object sender, GSMEventArgs e);

        //事件
        public event AddNumEventHandler AddNumEvent;

        public Form9()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Regex.IsMatch(textBox2.Text, @"^(1[3|5|8][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9])$"))
            {
                //引发事件
                if (AddNumEvent != null)
                {
                    GSMEventArgs ge = new GSMEventArgs();
                    ge.Message = textBox1.Text + "," + textBox2.Text + "," + textBox3.Text;
                    AddNumEvent(this, ge);
                }
                this.Close();
            }
            else
            {
                MessageBox.Show("手机号码不正确");
            }
        }

        private void Form9_Load(object sender, EventArgs e)
        {
            
        }
    }
}
