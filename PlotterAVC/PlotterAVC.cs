using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using StructsDados;

namespace PlotterAVC
{
    public partial class PlotterAvc : Form
    {

        public PlotterAvc()
        {
            InitializeComponent();
            _serialPort = new SerialPort();
        }

        private void ConectarSerial()
        {
            if (Conectado)
            {
                Desconectar();
                btConectar.Text = @"Conectar";
                timerGraph.Enabled = false;
                timerLista.Enabled = false;
            }
            else if (Conectar())
            {
                btConectar.Text = @"Conectado";
                timerGraph.Enabled = true;
                timerLista.Enabled = true;
            }
            else
            {
                btConectar.Text = @"Conectar";
                timerGraph.Enabled = false;
                timerLista.Enabled = false;
            }
        }

        private void BtConectar_Click(object sender, EventArgs e)
        {
            ConectarSerial();
        }

        private static void MinMax(ref double minimum, ref double maximum, int decimais = 1)
        {
            if (minimum == maximum)
                return;
            var min = Math.Round(minimum, decimais);
            var max = Math.Round(maximum, decimais++);
            while (min == max)
            {
                min = Math.Round(minimum, decimais);
                max = Math.Round(maximum, decimais++);
            }
            minimum = min;
            maximum = max;
        }

        private void AtualizaGraph()
        {
            chartAVC.Series[0].Points.Clear();
            chartAVC.Series[1].Points.Clear();

            for (var i = 0; i < _varsAvc.Count; i++)
            {
                chartAVC.Series[0].Points.AddXY(_varsAvc[i].Tempo, _varsAvc[i].Referencia);
                chartAVC.Series[1].Points.AddXY(_varsAvc[i].Tempo, _varsAvc[i].Arco);
            }

            if (_varsAvc.Count == 0)
            {
                chartAVC.ChartAreas[0].AxisX.Maximum = 1;
                chartAVC.ChartAreas[0].AxisX.Minimum = 0;
                chartAVC.ChartAreas[0].AxisY.Maximum = 15;
                chartAVC.ChartAreas[0].AxisY.Minimum = 0;
            }
            else
            {
                chartAVC.ChartAreas[0].AxisX.Minimum = _varsAvc.Min(dadosAvc => dadosAvc.Tempo);
                chartAVC.ChartAreas[0].AxisX.Maximum = _varsAvc.Max(dadosAvc => dadosAvc.Tempo);
                chartAVC.ChartAreas[0].AxisY.Minimum = 0;//_varsAvc.Min(dadosAvc => dadosAvc.Referencia < dadosAvc.Arco ? dadosAvc.Referencia : dadosAvc.Arco);
                chartAVC.ChartAreas[0].AxisY.Maximum = _varsAvc.Max(dadosAvc => dadosAvc.Referencia > dadosAvc.Arco ? dadosAvc.Referencia : dadosAvc.Arco) + 5;
            }
            chartAVC.ChartAreas[0].AxisX.IntervalAutoMode = IntervalAutoMode.VariableCount;
            chartAVC.ChartAreas[0].AxisY.IntervalAutoMode = IntervalAutoMode.VariableCount;
            var min = chartAVC.ChartAreas[0].AxisX.Minimum;
            var max = chartAVC.ChartAreas[0].AxisX.Maximum;
            MinMax(ref min, ref max);
            chartAVC.ChartAreas[0].AxisX.Minimum = min;
            chartAVC.ChartAreas[0].AxisX.Maximum = max;
            min = chartAVC.ChartAreas[0].AxisY.Minimum;
            max = chartAVC.ChartAreas[0].AxisY.Maximum;
            MinMax(ref min, ref max);
            chartAVC.ChartAreas[0].AxisY.Minimum = min;
            chartAVC.ChartAreas[0].AxisY.Maximum = max;
        }

        private void TimerGraph_Tick(object sender, EventArgs e)
        {
            if (!Visible)
                return;
            AtualizaGraph();
        }

        private void BtConectar_MouseDown(object sender, MouseEventArgs e)
        {
            if (!Conectado)
                btConectar.Text = @"Conectando..";
        }

        private void BtExportar_Click(object sender, EventArgs e)
        {
            Aquisicao.DialogoSaveAquis(_saveDialogAvc, _varsAvc)();
        }

        private void BtReset_Click(object sender, EventArgs e)
        {
            _varsAvc.Clear();
            _countAnt = 0;
        }

        private void PlotterAVC_Load(object sender, EventArgs e)
        {
            if (!Conectado)
                btConectar.Text = @"Conectando..";
            ConectarSerial();
        }
    }
}
