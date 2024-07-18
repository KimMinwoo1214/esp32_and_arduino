import serial
import time
import random

# 시리얼 포트와 보드레이트 설정
arduino_port = 'COM4' 
baud_rate = 9600  # 아두이노와 일치하는 보드레이트 설정

# 시리얼 포트 열기
ser = serial.Serial(arduino_port, baud_rate, timeout=1)
time.sleep(2)  # 포트가 열릴 때까지 잠시 대기

def send_string_to_arduino(string):
    try:
        # 문자열을 바이트로 인코딩하여 전송
        ser.write(string.encode())
        print(f"Sent: {string}")
    except Exception as e:
        print(f"Error: {e}")

while True:
    uga = str(random.randint(1, 500))
    str_uga = "a" + uga + "b \n"

    # 문자열 전송
    send_string_to_arduino(str_uga)
    
    text = input("Continue?(y or n)")
    
    if text == 'n':
        break

# 시리얼 포트 닫기
ser.close()
