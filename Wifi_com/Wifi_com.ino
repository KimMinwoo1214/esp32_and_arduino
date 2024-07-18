#include <WiFi.h>

#define ssid  "ConnectValue_A401_2G"
#define password   "CVA401!@#$"

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);  // WiFi 연결 시작
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");  // 연결 시도 중 상태 표시
    }
    Serial.print("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());  // WiFi 연결 성공 시 IP 주소 출력
}

void loop() {
    WiFiClient client;
    if(!client.connect(IPAddress(172, 30, 1, 92), 10000)) {  // 서버에 연결 시도
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }

    String inputString = "";
    while (Serial.available() > 0) {
        char c = Serial.read();  // 시리얼 입력 읽기
        inputString += c;  // 문자열에 추가
        delay(10);  // 시리얼 데이터 읽기 대기 시간 (필요에 따라 조정)
    }

    if (inputString.length() > 0) {
        client.print(inputString);  // 문자열 전체를 한 번에 전송
        Serial.print("Sent: ");
        Serial.println(inputString);  // 전송된 데이터 확인용
    }

    client.stop();  // 클라이언트 연결 종료
    delay(100);
}
