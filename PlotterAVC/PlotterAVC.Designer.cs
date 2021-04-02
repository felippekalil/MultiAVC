namespace PlotterAVC
{
    partial class PlotterAvc
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlotterAvc));
            this.chartAVC = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.btConectar = new System.Windows.Forms.Button();
            this.lb1 = new System.Windows.Forms.Label();
            this.lbTaxa = new System.Windows.Forms.Label();
            this.timerSerial = new System.Windows.Forms.Timer(this.components);
            this.timerGraph = new System.Windows.Forms.Timer(this.components);
            this.timerLista = new System.Windows.Forms.Timer(this.components);
            this.btExportar = new System.Windows.Forms.Button();
            this.btReset = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chartAVC)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // chartAVC
            // 
            this.chartAVC.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chartAVC.BackColor = System.Drawing.Color.Transparent;
            chartArea1.AxisX.LabelStyle.ForeColor = System.Drawing.Color.White;
            chartArea1.AxisX.LineColor = System.Drawing.Color.White;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisX.MajorGrid.LineColor = System.Drawing.Color.White;
            chartArea1.AxisX.MajorTickMark.LineColor = System.Drawing.Color.White;
            chartArea1.AxisX.Title = "Tempo (s)";
            chartArea1.AxisX.TitleForeColor = System.Drawing.Color.White;
            chartArea1.AxisY.LabelStyle.ForeColor = System.Drawing.Color.White;
            chartArea1.AxisY.LineColor = System.Drawing.Color.White;
            chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.Gray;
            chartArea1.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea1.AxisY.MajorTickMark.LineColor = System.Drawing.Color.White;
            chartArea1.AxisY.TitleForeColor = System.Drawing.Color.White;
            chartArea1.BackColor = System.Drawing.Color.Transparent;
            chartArea1.BorderColor = System.Drawing.Color.White;
            chartArea1.Name = "DadosAVC";
            this.chartAVC.ChartAreas.Add(chartArea1);
            legend1.BackColor = System.Drawing.Color.Transparent;
            legend1.ForeColor = System.Drawing.Color.White;
            legend1.Name = "Legend1";
            legend1.TitleBackColor = System.Drawing.Color.Transparent;
            this.chartAVC.Legends.Add(legend1);
            this.chartAVC.Location = new System.Drawing.Point(169, 12);
            this.chartAVC.Name = "chartAVC";
            series1.ChartArea = "DadosAVC";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series1.Legend = "Legend1";
            series1.Name = "Ref";
            series2.ChartArea = "DadosAVC";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            series2.Legend = "Legend1";
            series2.Name = "Arco";
            this.chartAVC.Series.Add(series1);
            this.chartAVC.Series.Add(series2);
            this.chartAVC.Size = new System.Drawing.Size(660, 414);
            this.chartAVC.TabIndex = 0;
            this.chartAVC.Text = "chartAVC";
            // 
            // btConectar
            // 
            this.btConectar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btConectar.FlatAppearance.BorderSize = 2;
            this.btConectar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btConectar.ForeColor = System.Drawing.Color.Silver;
            this.btConectar.Location = new System.Drawing.Point(48, 366);
            this.btConectar.Name = "btConectar";
            this.btConectar.Size = new System.Drawing.Size(97, 23);
            this.btConectar.TabIndex = 1;
            this.btConectar.Text = "Conectar";
            this.btConectar.UseVisualStyleBackColor = true;
            this.btConectar.Click += new System.EventHandler(this.BtConectar_Click);
            this.btConectar.MouseDown += new System.Windows.Forms.MouseEventHandler(this.BtConectar_MouseDown);
            // 
            // lb1
            // 
            this.lb1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lb1.AutoSize = true;
            this.lb1.ForeColor = System.Drawing.SystemColors.Control;
            this.lb1.Location = new System.Drawing.Point(25, 405);
            this.lb1.Name = "lb1";
            this.lb1.Size = new System.Drawing.Size(83, 13);
            this.lb1.TabIndex = 2;
            this.lb1.Text = "Taxa Aquisição:";
            // 
            // lbTaxa
            // 
            this.lbTaxa.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lbTaxa.AutoSize = true;
            this.lbTaxa.ForeColor = System.Drawing.SystemColors.Control;
            this.lbTaxa.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.lbTaxa.Location = new System.Drawing.Point(110, 405);
            this.lbTaxa.Name = "lbTaxa";
            this.lbTaxa.Size = new System.Drawing.Size(35, 13);
            this.lbTaxa.TabIndex = 3;
            this.lbTaxa.Text = "10 Hz";
            // 
            // timerGraph
            // 
            this.timerGraph.Tick += new System.EventHandler(this.TimerGraph_Tick);
            // 
            // timerLista
            // 
            this.timerLista.Tick += new System.EventHandler(this.TimerLista_Tick);
            // 
            // btExportar
            // 
            this.btExportar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btExportar.FlatAppearance.BorderSize = 2;
            this.btExportar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btExportar.ForeColor = System.Drawing.Color.Silver;
            this.btExportar.Location = new System.Drawing.Point(737, 85);
            this.btExportar.Name = "btExportar";
            this.btExportar.Size = new System.Drawing.Size(60, 23);
            this.btExportar.TabIndex = 4;
            this.btExportar.Text = "Exportar";
            this.btExportar.UseVisualStyleBackColor = true;
            this.btExportar.Click += new System.EventHandler(this.BtExportar_Click);
            // 
            // btReset
            // 
            this.btReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btReset.FlatAppearance.BorderSize = 2;
            this.btReset.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btReset.ForeColor = System.Drawing.Color.Silver;
            this.btReset.Location = new System.Drawing.Point(736, 392);
            this.btReset.Name = "btReset";
            this.btReset.Size = new System.Drawing.Size(61, 23);
            this.btReset.TabIndex = 5;
            this.btReset.Text = "Reset";
            this.btReset.UseVisualStyleBackColor = true;
            this.btReset.Click += new System.EventHandler(this.BtReset_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::PlotterAVC.Properties.Resources.logo_labsolda_ha;
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(174, 45);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(69, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(117, 19);
            this.label1.TabIndex = 7;
            this.label1.Text = "MotoAVC v1.0";
            // 
            // PlotterAvc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(50)))), ((int)(((byte)(50)))), ((int)(((byte)(50)))));
            this.ClientSize = new System.Drawing.Size(809, 427);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.btReset);
            this.Controls.Add(this.btExportar);
            this.Controls.Add(this.lbTaxa);
            this.Controls.Add(this.lb1);
            this.Controls.Add(this.btConectar);
            this.Controls.Add(this.chartAVC);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "PlotterAvc";
            this.Text = "Plotter AVC";
            this.Load += new System.EventHandler(this.PlotterAVC_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chartAVC)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chartAVC;
        private System.Windows.Forms.Button btConectar;
        private System.Windows.Forms.Label lb1;
        private System.Windows.Forms.Label lbTaxa;
        private System.Windows.Forms.Timer timerSerial;
        private System.Windows.Forms.Timer timerGraph;
        private System.Windows.Forms.Timer timerLista;
        private System.Windows.Forms.Button btExportar;
        private System.Windows.Forms.Button btReset;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
    }
}

