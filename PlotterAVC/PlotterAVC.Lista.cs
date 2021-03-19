using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PlotterAVC
{
    public partial class PlotterAvc
    {
        private int _countAnt;
        private double _taxa = 10;
        private const double AlphaTaxa = 0.1;

        private struct VarsAvc
        {
            public double Referencia, Arco, Tempo;
        }

        private readonly List<VarsAvc> _varsAvc = new List<VarsAvc>();

        private readonly SaveFileDialog _saveDialogAvc = new SaveFileDialog
        {
            InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop),
            FileName = "AVC.txt",
            Filter = @"Arquivos AVC|*.txt|Todos Arquivos|*.*",
            FilterIndex = 1
        };

        private static int LocalizaItem(byte item, IReadOnlyList<byte> dadoSerial, int offset = 0)
        {
            for (var i = offset; i < dadoSerial.Count; i++)
                if (dadoSerial[i] == item)
                    return i;
            return -1;
        }

        private void AddListaDados()
        {
            while (_bufferIn.Length > 7)
            {
                if (!(_bufferIn.Contains(' ')
                      && _bufferIn.Contains('\r'))
                    && _bufferIn.Contains('\n'))
                    _bufferIn = _bufferIn.Remove(0, 1);
                var espaco = _bufferIn.IndexOf(' ');
                var quebra = _bufferIn.IndexOf('\r');
                if (espaco == -1 || quebra == -1)
                    return;
                if (espaco > quebra)
                {
                    _bufferIn = _bufferIn.Remove(0, quebra + 1);
                    return;
                }

                double var1, var2;
                try
                {
                    var1 = Convert.ToDouble(_bufferIn.Substring(0, espaco).Replace('.', ','));
                    var2 = Convert.ToDouble(_bufferIn.Substring(espaco + 1, quebra - espaco - 1).Replace('.', ','));
                }
                catch
                {
                    _bufferIn = _bufferIn.Remove(0, quebra + 2);
                    continue;
                }

                if (var1 != 3.2)
                    var1 = var1;

                var tAnt = _varsAvc?.Count > 0 ? _varsAvc.Last().Tempo : 0;
                var varAvc = new VarsAvc
                {
                    Referencia = Convert.ToDouble(var1),
                    Arco = Convert.ToDouble(var2),
                    Tempo = Math.Round(_taxa > 0 ? 1 / _taxa : 0, 1) + tAnt
                };

                var contRemove = quebra + 2;
                for(var i = 0; i < contRemove && _bufferIn.Length > 0; i++)
                    _bufferIn = _bufferIn.Remove(0, 1);

                _varsAvc.Add(varAvc);
            }
        }

        private void TimerLista_Tick(object sender, EventArgs e)
        {
            AddListaDados();
            var delta = _varsAvc.Count - _countAnt;
            _countAnt = _varsAvc.Count;
            var taxaAtual = 1000 * delta / timerLista.Interval;
            _taxa = taxaAtual * AlphaTaxa + _taxa * (1 - AlphaTaxa);
            lbTaxa.Text = _taxa.ToString("F1") + @" Hz";
        }

    }
}
