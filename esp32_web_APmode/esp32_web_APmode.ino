#include <WiFi.h>
#include <WebServer.h>

#define M1_B    26
#define M1_A    27
#define M2_B    12
#define M2_A    14
#define M3_B    15
#define M3_A    2
#define M4_B    4
#define M4_A    16

#define FORWARD   1
#define BACKWARD  2
#define STOP      3

/* Put your SSID & Password */
const char* ssid = "esp32_kmw";  // Enter SSID here
const char* password = "123456789";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

int motor_status = STOP;

WebServer server(80); 

void go_forward(){
  Serial.println("forward");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);

  digitalWrite(M3_A, HIGH);
  digitalWrite(M3_B, LOW);
  digitalWrite(M4_A, HIGH);
  digitalWrite(M4_B, LOW);
   
}

void go_backward(){
  Serial.println("backward");
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, HIGH);
  digitalWrite(M2_B, LOW);

  digitalWrite(M3_A, LOW);
  digitalWrite(M3_B, HIGH);
  digitalWrite(M4_A, LOW);
  digitalWrite(M4_B, HIGH);
}

void turn_right(){
  Serial.println("right");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);

  digitalWrite(M3_A, LOW);
  digitalWrite(M3_B, HIGH);
  digitalWrite(M4_A, LOW);
  digitalWrite(M4_B, HIGH);
}

void turn_left(){
  Serial.println("left");
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, HIGH);
  digitalWrite(M2_B, LOW);

  digitalWrite(M3_A, HIGH);
  digitalWrite(M3_B, LOW);
  digitalWrite(M4_A, HIGH);
  digitalWrite(M4_B, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, LOW);
  
  digitalWrite(M3_A, LOW);
  digitalWrite(M3_B, LOW);
  digitalWrite(M4_A, LOW);
  digitalWrite(M4_B, LOW);
  delay(200);
}

void setup() {
  Serial.begin(115200);

  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
  pinMode(M3_A, OUTPUT);
  pinMode(M3_B, OUTPUT);
  pinMode(M4_A, OUTPUT);
  pinMode(M4_B, OUTPUT);

  stop();

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/forward", handle_forward);
  server.on("/backward", handle_backward);
  server.on("/stop", handle_stop);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  
}

void handle_OnConnect() {
  stop();
  Serial.println("motor stop");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_forward() {
  go_forward();
  motor_status = FORWARD;
  Serial.println("motor forward");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_backward() {
  go_backward();
  motor_status = BACKWARD;
  Serial.println("motor backward");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_stop() {
  stop();
  motor_status = STOP;
  Serial.println("motor stop");
  server.send(200, "text/html", SendHTML(motor_status)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t motor_status){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

  switch(motor_status){
    case 1:
      {ptr +="<p>Motor forward</p><a class=\"button button-on\" href=\"/forward\">ON</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-off\" href=\"/backward\">OFF</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-off\" href=\"/stop\">OFF</a>\n";}
      break;
    case 2:
      {ptr +="<p>Motor forward</p><a class=\"button button-off\" href=\"/forward\">OFF</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-on\" href=\"/backward\">ON</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-off\" href=\"/stop\">OFF</a>\n";}
      break;
    case 3:
      {ptr +="<p>Motor forward</p><a class=\"button button-off\" href=\"/forward\">OFF</a>\n";}
      {ptr +="<p>Motor backward</p><a class=\"button button-off\" href=\"/backward\">OFF</a>\n";}
      {ptr +="<p>stop</p><a class=\"button button-on\" href=\"/stop\">ON</a>\n";}
      break;
  }
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}