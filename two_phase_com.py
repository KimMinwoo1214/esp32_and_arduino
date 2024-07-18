import serial
import time
import threading

# 시리얼 포트 설정
port = 'COM4'  # 사용하는 시리얼 포트 이름 변경 필요
baudrate = 9600  # 보드레이트 설정
timeout = 1  # 타임아웃 설정 (초 단위)

ser = serial.Serial(port, baudrate, timeout=timeout)
count = 0

def receive_serial():
    while True:
        if ser.in_waiting:
            command = ser.readline()
            cmd_dec = command.decode().strip()
            print(f"Received from Arduino: {cmd_dec}")
            time.sleep(0.05)

def send_serial():
    global count
    while True:
        # 보낼 문자열 설정
        message = f'a{count}b\n'
        count += 1

        # 문자열 전송
        print(f"Sent to Arduino: {message.strip()}")
        ser.write(message.encode('utf-8'))

        # 시리얼 포트 닫기
        time.sleep(1)

# 두 개의 쓰레드를 사용하여 송신과 수신을 동시에 수행
receive_thread = threading.Thread(target=receive_serial)
send_thread = threading.Thread(target=send_serial)

receive_thread.start()
send_thread.start()
