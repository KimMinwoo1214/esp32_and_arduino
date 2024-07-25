import sys
import serial
import time
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, QTextEdit

class ArduinoMonitor(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

        # 시리얼 포트와 보드레이트 설정
        self.arduino_port = 'COM3'
        self.baud_rate = 9600  # 아두이노와 일치하는 보드레이트 설정
        self.ser = serial.Serial(self.arduino_port, self.baud_rate, timeout=1)
        time.sleep(2)  # 포트가 열릴 때까지 잠시 대기

        self.timer = self.startTimer(1)  # 1ms마다 업데이트

    def initUI(self):
        self.setWindowTitle('Serial Monitor')
        self.setGeometry(100, 100, 400, 300)

        self.layout = QVBoxLayout()

        self.Encoder1Label = QLabel('Encoder1 Value: ')
        self.Encoder2Label = QLabel('Encoder2 Value: ')
        self.outputText = QTextEdit()
        self.outputText.setReadOnly(True)

        self.layout.addWidget(self.Encoder1Label)
        self.layout.addWidget(self.Encoder2Label)
        self.layout.addWidget(self.outputText)

        self.setLayout(self.layout)

    def timerEvent(self, event):
        self.read_from_arduino()

    def read_from_arduino(self):
        try:
            if self.ser.in_waiting > 0:
                received = self.ser.readline().decode('utf-8').rstrip()
                receiced_values = received.split(',')
                Encoder1 = receiced_values[0]
                Encoder2 = receiced_values[1]
                self.Encoder1Label.setText(f"Encoder1 value: {Encoder1}")
                self.Encoder2Label.setText(f"Encoder2 value: {Encoder2}")
                self.outputText.append(f"Encoder1 value: {Encoder1}")
                self.outputText.append(f"Encoder2 value: {Encoder2}")
        except Exception as e:
            self.outputText.append(f"Error: {e}")

    def closeEvent(self, event):
        self.ser.close()
        event.accept()

if __name__ == '__main__':
    applacation = QApplication(sys.argv)
    ex = ArduinoMonitor()
    ex.show()
    sys.exit(applacation.exec_())
