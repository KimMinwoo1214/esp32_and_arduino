#define Encoder_output_1 2 // 첫 번째 엔코더의 인터럽트 핀 (Arduino의 2번 핀)
#define Encoder_output_2 3 // 두 번째 엔코더의 인터럽트 핀 (Arduino의 3번 핀)

volatile int count1 = 0;
volatile int count2 = 0;

void setup() {
  Serial.begin(9600); // baudrate 9600

  // 첫 번째 엔코더 핀 설정
  pinMode(Encoder_output_1, INPUT);

  // 두 번째 엔코더 핀 설정
  pinMode(Encoder_output_2, INPUT);

  // 첫 번째 엔코더 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(Encoder_output_1), Encoder_1, CHANGE);

  // 두 번째 엔코더 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(Encoder_output_2), Encoder_2, CHANGE);

  Serial.println("Setup complete"); // 디버깅 메시지 출력
}

void loop() {
  // 0.1초마다 펄스 카운트 값을 시리얼 모니터에 출력
  static unsigned long last_time = 0;
  static unsigned long reset_time = 0;
  unsigned long current_time = millis();

  if (current_time - last_time >= 100) { // 0.1초마다 실행
    String message = String(count1) + "," + String(count2); // 두 값을 쉼표로 구분하여 문자열로 변환
    Serial.println(message);

    last_time = current_time;
  }

  if (current_time - reset_time >= 5000) { // 5초마다 실행
    count1 = 0;
    count2 = 0;
    reset_time = current_time;
  }
}

// 첫 번째 엔코더 인터럽트 핸들러
void Encoder_1() {
  count1++;
}

// 두 번째 엔코더 인터럽트 핸들러
void Encoder_2() {
  count2++;
}
