using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PlotterAVC
{
    public partial class PlotterAvc
    {
        private readonly SerialPort _serialPort;

        private string _bufferIn;

        private bool Conectado => _serialPort.IsOpen;

        private void Desconectar()
        {
            _serialPort.Close();
        }

        private static bool MensagemFazSentido(string dado)
        {
            return dado.Length > 7 && dado.Contains(' ') && dado.Contains('\r');
        }

        private bool Conectar()
        {
            _serialPort.Close();
            foreach (var str in SerialPort.GetPortNames())
            {
                var tmp = new SerialPort(str);
                if (tmp.IsOpen) continue;
                _serialPort.PortName = str;
                try
                {
                    _serialPort.Open();
                    _serialPort.BaudRate = 9600;
                    _serialPort.Parity = Parity.None;
                    _serialPort.DiscardInBuffer();

                    Thread.Sleep(2000); // aguarda chegar alguma coisa

                    var s = _serialPort.ReadExisting();
                    if (MensagemFazSentido(s))
                    {
                        timerSerial.Enabled = true;
                        _serialPort.DiscardInBuffer();
                        _serialPort.DataReceived += SerialPort_DataReceived;
                        return true; //break;
                    }
                    timerSerial.Enabled = false;
                    _serialPort.DiscardInBuffer();
                    _serialPort.DataReceived -= SerialPort_DataReceived;
                    Desconectar();
                }
                catch { _serialPort.Close(); }
            }
            Desconectar();
            return false;
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            _bufferIn += _serialPort.ReadExisting();
            _serialPort.DiscardInBuffer();
        }
    }
}
