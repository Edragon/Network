using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace 短信猫
{
    public partial class Form5 : Form
    {
        //委托 收到短信时回调
        delegate void RecievedMsgHandler(string s);
        //回调  收到信息 设备打开时有未读信息
        RecievedMsgHandler RecievedMsg = null;

        //回调，
        RecievedMsgHandler HaveUnreadMsg = null;
 
        public Form5()
        {
            InitializeComponent();
        }

        private void Form5_Load(object sender, EventArgs e)
        {

            //添加事件，收到短信
            Program.gm.OnRecieved += new GSMMODEM.GSMModem.OnRecievedHandler(gm_OnRecieved);
            //实例化回调函数
            RecievedMsg = new RecievedMsgHandler(UpdateCtrols);

            //设备打开事件
            Form6 f6 = (Form6)this.Parent.GetNextControl(this, true);
            f6.GSMOpen += new Form6.GSMOpenHandler(f6_GSMOpen);

            HaveUnreadMsg = new RecievedMsgHandler(UpdateCtrols);
        }

        void f6_GSMOpen(object sender, GSMEventArgs ge)
        {
            string[] strs = null;
            try
            {
                strs = Program.gm.GetUnreadMsg();
                if (strs == null) return;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }

            foreach (string s in strs)
            {
                if (s == null || s.Length == 0)                 //未读信息已读完
                {
                    return;
                }

                //把收到短信内容写入文件
                using (StreamWriter sw = File.AppendText("已收短信.txt"))
                {
                    sw.WriteLine(s);
                    sw.Close();
                }

                Invoke(HaveUnreadMsg,s);
            }
        }

        /// <summary>
        /// 收到短信后，对相关控件更新
        /// </summary>
        /// <param name="ge">参数</param>
        private void UpdateCtrols(string s)
        {
            listView3.Items.Add(s.Split(',')[1]);
            listView3.Items[listView3.Items.Count - 1].SubItems.Add(s.Split(',')[3]);
            listView3.Items[listView3.Items.Count - 1].SubItems.Add(s.Split(',')[0]);
            listView3.Items[listView3.Items.Count - 1].SubItems.Add(s.Split(',')[2]);
        }

        /// <summary>
        /// 收到新短信
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void gm_OnRecieved(object sender, EventArgs e)
        {
            string s = Program.gm.ReadNewMsg();

            //把收到短信内容写入文件
            using (StreamWriter sw = File.AppendText("已收短信.txt"))
            {
                sw.WriteLine(s);
                sw.Close();
            }
            
            //回调
            Invoke(RecievedMsg, s);
        }

        //详细信息
        private void button19_Click(object sender, EventArgs e)
        {
            if (listView3.SelectedItems.Count == 0)
            {
                MessageBox.Show("没有选择项");
                return;
            }

            Form8 f8 = new Form8(listView3.SelectedItems[0].SubItems[2].Text,
                listView3.SelectedItems[0].SubItems[3].Text,
                listView3.SelectedItems[0].SubItems[0].Text,
                listView3.SelectedItems[0].SubItems[1].Text);
            f8.TopLevel = false;
            f8.FormBorderStyle = FormBorderStyle.None;
            f8.Parent = this.Parent;
            f8.Show();

            f8.BringToFront();
        }

        //回复
        private void button20_Click(object sender, EventArgs e)
        {
            button19_Click(sender, e);
        }

        private void listView3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
