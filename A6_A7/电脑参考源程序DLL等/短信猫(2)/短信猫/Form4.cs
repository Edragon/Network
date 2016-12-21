using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Text.RegularExpressions;
using System.Threading;

namespace 短信猫
{
    public partial class Form4 : Form
    {
        //MsgList声明 存储要发送的短信内容和号码
        MsgList msgList = null;

        public Form4()
        {
            InitializeComponent();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            //xPath指示excel文件路径
            string xPath = null;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Excel Files(*.xls)|*.xls";
            openFileDialog1.Title = "导入手机号码";
            listView2.SelectedItems.Clear();
            // Show the Dialog.
            // If the user clicked OK in the dialog and
            // a .CUR file was selected, open it.
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                xPath = openFileDialog1.FileName;
                string strCon;
                strCon = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + xPath + ";Extended Properties='Excel 8.0;HDR=False;IMEX=1'";
                OleDbConnection OleConn = new OleDbConnection(strCon);
                string sql = "SELECT * FROM  [Sheet1$]";
                DataSet ds = new DataSet();
                try
                {
                    OleConn.Open();
                    OleDbDataAdapter da = new OleDbDataAdapter(sql, strCon);
                    da.Fill(ds, "sheet1");
                    OleConn.Close();
                }
                catch
                {
                    MessageBox.Show("无法打开！\n请关闭其他打开此文件的程序后再试");
                }
                DataTable dt = ds.Tables[0];
                try
                {
                    foreach (DataRow row in dt.Rows)
                    {
                        string str = row["手机号码"].ToString();
                        if (Regex.IsMatch(str, @"^(1[3|5|8][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9])$"))
                        {
                            ListViewItem lvi = new ListViewItem(str);
                            lvi.SubItems.Add(row["姓名"].ToString());
                            lvi.SubItems.Add(row["备注"].ToString());
                            listView2.Items.Add(lvi);
                        }
                        else
                        {
                            MessageBox.Show("表格第二列不是手机号码或是有错误号码!\n请检查后再试");
                            break;
                        }
                    }
                }
                catch
                {
                    MessageBox.Show("程序支持文件为前三列都有内容的xls表格\n第一列“姓名”，第二列“手机号码”，第三列“备注”");
                }
            }

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            label4.Text = textBox1.Text.Length.ToString() + "/70";
            if (textBox1.Text.Length <= 70)
            {
                label4.ForeColor = Color.Green;
            }
            else
            {
                label4.ForeColor = Color.Red;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            ListView.SelectedIndexCollection numToRemove = listView2.SelectedIndices;
            try
            {
                int j = 0;
                foreach (int i in numToRemove)
                {
                    listView2.Items.RemoveAt(i - j);
                    j = j + 1;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Form9 adNum = new Form9();
            adNum.Owner = this;

            //事件 传值
            adNum.AddNumEvent += new Form9.AddNumEventHandler(adNum_AddNumEvent);

            adNum.ShowDialog();
        }

        void adNum_AddNumEvent(object sender, GSMEventArgs e)
        {
            string[] s = e.Message.Split(',');

            listView2.Items.Add(s[1]);
            listView2.Items[listView2.Items.Count - 1].SubItems.Add(s[0]);
            listView2.Items[listView2.Items.Count - 1].SubItems.Add(s[2]);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 70)
            {
                MessageBox.Show("短信字数太长");
                return;
            }
            else if (textBox1.Text.Length == 0)
            {
                MessageBox.Show("不允许发送空短信");
            }
            else if (listView2.Items.Count == 0||listView2.Items.Count>255)
            {
                MessageBox.Show("没有号码或是号码超过255个");
            }
            else if (msgList != null)
            {
                MessageBox.Show("上一条尚未发送完成！无法发送");
            }
            else
            {
                //发送短信时 对应有控件显示
                progressBar1.Visible = true;
                progressBar1.Minimum = 0;
                progressBar1.Maximum = listView2.Items.Count;
                progressBar1.Value = 0;

                label5.Visible = true;
                label5.Text = "正在发送";
                label5.ForeColor = Color.Black;

                string[] s = new string[255];
                for (int i = 0; i < listView2.Items.Count; i++)
                {
                    s[i] = listView2.Items[i].Text;
                }
                msgList = new MsgList(s, textBox1.Text);
                SendOneMsg = new SendEventHandler(OnSendOneMsg);

                Thread threadSendMsg = new Thread(SendMsg);
                threadSendMsg.Start();
            }
        }


        void OnSendOneMsg(object sender, GSMEventArgs ge)
        {
            if (ge.Message.Substring(0, 4) == "发送失败")
            {
                label5.Text = "发送失败";
                label5.ForeColor = Color.Red;

                msgList = null;
            }
            else if (ge.Message.Substring(0, 4) == "发送完成")
            {
                //发送完成，控件隐藏
                label5.Visible = false;
                progressBar1.Visible = false;
                label5.Text = "发送完成";
                label5.ForeColor = Color.Green;

                msgList = null;
            }
            else
            {
                progressBar1.Value += 1;
            }
        }

        //委托 完成窗体的变化 事件
        delegate void SendEventHandler(object sender, GSMEventArgs ge);

        //异步调用 每发送一条调用一次
        SendEventHandler SendOneMsg = null;

        private void SendMsg()
        {
            foreach (string s in msgList.PhoneList)
            {
                if (s != null && s.Length != 0)
                {
                    try
                    {
                        Program.gm.SendMsg(s, msgList.Msg);
                        GSMEventArgs ge = new GSMEventArgs();
                        ge.Message = s;
                        //SendOneMsg(this, ge);
                        Invoke(SendOneMsg,this,ge);
                    }
                    catch
                    {
                        GSMEventArgs ge = new GSMEventArgs();
                        ge.Message = "发送失败" + s;
                        Invoke(SendOneMsg, this, ge);
                        return;
                    }
                }
                else
                {
                    GSMEventArgs ge = new GSMEventArgs();
                    ge.Message = "发送完成";
                    Invoke(SendOneMsg, this, ge);
                }
            }
        }

        private void Form4_Load(object sender, EventArgs e)
        {
            label5.Visible = false;
            progressBar1.Visible = false;
        }
    }

    //类 MsgList 每次发送创建对象，开启另一线程 根据此类的数据发送短信
    class MsgList
    {
        public MsgList(string[] phonelist, string msg)
        {
            PhoneList = phonelist;
            Msg = msg;
        }

        //号码列表
        public string[] PhoneList;

        //短信内容
        public string Msg;
    }
}
