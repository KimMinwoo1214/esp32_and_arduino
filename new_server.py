import asyncio
import websockets
import serial

# 아두이노가 연결된 시리얼 포트를 지정합니다.
# Windows의 경우: 'COM3', 'COM5' 등
# macOS 또는 Linux의 경우: '/dev/ttyUSB0', '/dev/ttyACM0' 등
arduino_port = 'COM5'
baud_rate = 115200

# 시리얼 통신 설정
ser = serial.Serial(arduino_port, baud_rate)

async def control_led(websocket, path):
    async for message in websocket:
        print(f"Received message: {message}")
        
        if message == "on":
            ser.write(b'1')  # LED 켜기 명령 전송
            await websocket.send("LED is ON")
        elif message == "off":
            ser.write(b'0')  # LED 끄기 명령 전송
            await websocket.send("LED is OFF")
        else:
            await websocket.send("Invalid command")

# WebSocket 서버 시작
start_server = websockets.serve(control_led, "0.0.0.0", 10000)

print("Starting WebSocket server on port 10000...")
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
