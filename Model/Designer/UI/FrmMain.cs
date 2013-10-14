﻿using System;
using System.Windows.Forms;
using xDockPanel;

namespace TCM.Model.Designer
{
    public partial class FrmMain : Form
    {
        private AppData App
        {
            get { return AppData.Instance; }
        }

        public FrmMain()
        {
            InitializeComponent();
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            App.FormToolbox.Show(paneldock, DockState.Left);
            App.FormProperty.Show(paneldock, DockState.Right);
            FrmDocument doc = new FrmDocument();
            doc.Show(paneldock, DockState.Document);
            //Library library = Library.Load(@"E:\Projects\Vapula\Core\Sample\library\sample_lib.tcm.xml");
            //library.Clear();
            //canvas.AddConnection(new Point(50, 50), new Point(100, 100));
        }

        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason != CloseReason.ApplicationExitCall)
            {
                if(MessageBox.Show(
                    "是否确定退出模型设计器？", "询问",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    Application.Exit();
                }
                else
                {
                    e.Cancel = true;
                }
            }
        }
    }
}