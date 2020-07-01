using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 프로젝트_2A
{
    public partial class Form1 : Form
    {
        [DllImport("advapi32.dll", EntryPoint = "LogonUser", SetLastError = true)]
        private static extern bool LogonUser(string userName, string domain, string password, int logonType, int logonProvider, out int token);

        public bool CheckPassword(string userName, string password)
        {
            //string userName = Environment.UserName;
            try
            {
                int token;
                bool result = LogonUser(userName, ".", password, 8, 0, out token);
                return result;
            }
            catch
            {
                return false;
            }
        }
        public Form1()
        {
            InitializeComponent();

            int w = SystemInformation.VirtualScreen.Width;
            int h = SystemInformation.VirtualScreen.Height;

            this.Size = new Size(w, h);
            this.StartPosition = FormStartPosition.Manual;
            this.Location = new Point(0, 0);

            this.FormBorderStyle = FormBorderStyle.None;

            this.ShowInTaskbar = false;
            this.BackColor = Color.White;
            label1.Text = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (CheckPassword(Environment.UserName, textBox1.Text))
            {
                this.WindowState = FormWindowState.Minimized;

            }
            else
            {
                label1.Text = "잘못된 입력입니다.";
                label1.ForeColor = Color.Red;
            }
        }
    }
}
