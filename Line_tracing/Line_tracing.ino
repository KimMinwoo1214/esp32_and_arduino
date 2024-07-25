int ENA = 10; // Enable pin for motor A (connected to PWM pin)
int ENB = 11; // Enable pin for motor B (connected to PWM pin)
int IN1 = 9;  // Control pin 1 for motor A
int IN2 = 8;  // Control pin 2 for motor A
int IN3 = 7;  // Control pin 1 for motor B
int IN4 = 6;  // Control pin 2 for motor B

void setup() {
  Serial.begin(115200); // 시리얼 통신 속도를 115200으로 설정
  
  // 모터 A 핀 설정
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // 모터 B 핀 설정
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'f') {
      // 모터 A 전진
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 255); // 최고 속도

      // 모터 B 전진
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 255); // 최고 속도
    } else if (c == 'b') {
      // 모터 A 후진
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 255); // 최고 속도

      // 모터 B 후진
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 255); // 최고 속도
    } else if (c == 's') {
      // 모터 A 정지s
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0); // 정지

      // 모터 B 정지
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0); // 정지
    }
  }
}
