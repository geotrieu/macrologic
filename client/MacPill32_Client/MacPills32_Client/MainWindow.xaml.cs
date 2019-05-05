using System;
using System.Windows;
using System.IO.Ports;

namespace MacPills32_Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        
        SerialPort _serialPort = new SerialPort("COM28", 9600, Parity.None, 8, StopBits.One);
        
        public MainWindow()
        {
            InitializeComponent();

            try
            {
                _serialPort.Open();
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void SendButton_OnClick(object sender, RoutedEventArgs e)
        {
            _serialPort.Write(RedTextBox.Text + "\r\n");
            _serialPort.Write(GreenTextBox.Text + "\r\n");
            _serialPort.Write(BlueTextBox.Text + "\r\n");
        }
    }
}