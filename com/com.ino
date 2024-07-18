#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);// Rx, Tx

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  // mySerial.println("Hello from Arduino");
  if (Serial.available() > 0) {
    String uga = Serial.readStringUntil('\n');
    int start = uga.indexOf('a');
    int end = uga.indexOf('b');
    // substring 하기
    String sub_uga = uga.substring(start+1, end);
    // Serial.println(sub_uga);
    mySerial.println(uga);
    mySerial.println(sub_uga);
  }
}