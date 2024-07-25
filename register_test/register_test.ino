#define EXTERNAL_SW 0x20 // PD5 핀
#define Encoder_output_1 0x04 // PD2 핀

volatile int count = 0;
volatile int val = 0;

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600); // baudrate 9600

  // 외부 스위치 설정
  DDRD &= ~EXTERNAL_SW; // 외부 스위치 핀을 입력으로 설정
  PORTD |= EXTERNAL_SW; // 풀업

  // 인터럽트 설정
  PCICR |= 0x04; // PCIE2 비트 활성
  PCMSK2 |= EXTERNAL_SW; // PCINT21 비트 활성화

  // 엔코더 인터럽트 설정 (레지스터 사용)
  DDRD &= ~Encoder_output_1; // 엔코더 핀을 입력으로 설정
  PORTD |= Encoder_output_1; // 풀업 저항
  EICRA |= (1 << ISC00); 
  EIMSK |= (1 << INT0);

  Serial.println("Setup complete"); // 디버깅 메시지 출력
}

void loop() {
  // 0.1초마다 펄스 카운트 값을 시리얼 모니터에 출력하고 5초마다 초기화
  static unsigned long last_time = 0;
  static unsigned long start_time = 0;
  unsigned long current_time = millis();
  
  if (current_time - last_time >= 100) {
    String message = String(count) + "," + String(val); // 두 값을 쉼표로 구분하여 문자열로 변환
    Serial.println(message);

    last_time = current_time;
  }
  
  if (current_time - start_time >= 5000) { // 5초마다 실행
    count = 0;
    val = 0;
    start_time = current_time;
  }
}

ISR(PCINT2_vect) {
  // 외부 스위치 인터럽트 처리
  val += 100;
}

ISR(INT0_vect) {
  // 엔코더 인터럽트 처리 (레지스터 사용)
  count++;
}
