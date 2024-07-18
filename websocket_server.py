import asyncio
import websocket

async def echo(websocket, path):
    async for message in websocket:
        print(f"Received message: {message}")
        await websocket.send(f"Echo: {message}")

start_server = websocket.server(echo, "0.0.0.0", 10000)

print("Starting WebSocket server on port 10000...")
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
