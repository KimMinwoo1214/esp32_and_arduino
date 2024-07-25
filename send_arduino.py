import serial
import time

# 시리얼 포트 설정
port = 'COM4'  # 사용하는 시리얼 포트 이름으로 변경 필요
baudrate = 9600  # 보드레이트 설정
timeout = 1  # 타임아웃 설정 (초 단위)

# 시리얼 포트 열기
ser = serial.Serial(port, baudrate, timeout=timeout)
time.sleep(2)  # 시리얼 포트가 열릴 때까지 잠시 대기

# 문자열 입력 및 전송
while True:
    user_input = input("문자열을 입력하세요 (If you want to stop, type stop): ")
    if user_input == "stop":
        break
    message = user_input + '\n'
    ser.write(message.encode('utf-8'))  # 문자열을 UTF-8로 인코딩하여 전송
    print(f"Sent to Arduino: {message.strip()}")
    time.sleep(1)  # 전송 후 잠시 대기

# 시리얼 포트 닫기
ser.close()

# 시리얼 포트 닫기
ser.close()
