#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  pinMode(13, OUTPUT);       // Set pin 13 as an output
  mySerial.begin(115200);    // Initialize SoftwareSerial communication with ESP32
  Serial.begin(115200);      // Initialize hardware serial communication for debugging
}

void loop() {
  if (mySerial.available()) {
    char command = mySerial.read();
    Serial.println(command); // Debugging: print received command
    if (command == '1') {
      digitalWrite(13, HIGH);  // Turn on LED
    } else if (command == '0') {
      digitalWrite(13, LOW);   // Turn off LED
    }
  }
}
