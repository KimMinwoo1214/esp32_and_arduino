#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // Rx, Tx

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!Serial) {
    ; // 시리얼 포트가 연결될 때까지 대기 (필요한 경우)
  }
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n'); // 개행 문자를 기준으로 문자열 수신
    Serial.println("Received: " + received); // 수신된 전체 문자열을 시리얼 모니터에 출력

    // 쉼표를 기준으로 문자열 분리
    int startIndex = 0;
    int commaIndex = received.indexOf(',');
    while (commaIndex != -1) {
      String part = received.substring(startIndex, commaIndex);
      Serial.println("Part: " + part); // 각 부분을 시리얼 모니터에 출력
      mySerial.println(part); // 각 부분을 SoftwareSerial 포트를 통해 출력

      startIndex = commaIndex + 1;
      commaIndex = received.indexOf(',', startIndex);
    }

    // 마지막 부분 처리
    String part = received.substring(startIndex);
    Serial.println("Part: " + part); // 마지막 부분을 시리얼 모니터에 출력
    mySerial.println(part); // 마지막 부분을 SoftwareSerial 포트를 통해 출력
  }
}
