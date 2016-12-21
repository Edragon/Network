using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace 短信猫
{
    public partial class Form2 : Form
    {
        //委托
        public delegate void F2EventHandler(object sender, GSMEventArgs e);

        //事件
        public event F2EventHandler F2Event;

        public Form2()
        {
            InitializeComponent();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button_Click(object sender, EventArgs e)
        {
            GSMEventArgs ge = new GSMEventArgs();
            ge.Message = ((Button)sender).Text;
            if (F2Event != null)
            {
                F2Event(this, ge);
            }
        }

    }
}
