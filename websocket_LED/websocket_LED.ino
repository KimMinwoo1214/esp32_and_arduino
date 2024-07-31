#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "ConnectValue_A401_2G";
const char* password = "CVA401!@#$";

WebSocketsServer webSocket = WebSocketsServer(80);

// Called when receiving any WebSocket message
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connection from ", num);
      Serial.println(ip.toString());
      break;
    }

    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      if (strcmp((char*)payload, "on") == 0) {
        Serial.write('1');  // Send '1' to Arduino to turn on the LED
      } else if (strcmp((char*)payload, "off") == 0) {
        Serial.write('0');  // Send '0' to Arduino to turn off the LED
      }
      webSocket.sendTXT(num, payload);  // Echo the message back to the client
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
  // Look for and handle WebSocket data
  webSocket.loop();
}
