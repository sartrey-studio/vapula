﻿namespace TCM.Model.Designer
{
    partial class UctParameter
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tooltip = new System.Windows.Forms.ToolTip(this.components);
            this.SuspendLayout();
            // 
            // UctParameter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Name = "UctParameter";
            this.Padding = new System.Windows.Forms.Padding(10, 6, 10, 6);
            this.Size = new System.Drawing.Size(200, 48);
            this.Leave += new System.EventHandler(this.UctParameter_Leave);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ToolTip tooltip;
    }
}
