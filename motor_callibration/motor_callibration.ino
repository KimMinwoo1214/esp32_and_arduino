#define Encoder_output_A 2 // pin2 of the Arduino
#define Encoder_output_B 3 // pin 3 of the Arduino

int ENA = 10; // Enable pin for motor A (connected to PWM pin)
int ENB = 11; // Enable pin for motor B (connected to PWM pin)
int IN1 = 9;  // Control pin 1 for motor A
int IN2 = 8;  // Control pin 2 for motor A
int IN3 = 7;  // Control pin 1 for motor B
int IN4 = 6;  // Control pin 2 for motor B

volatile int Count_pulses_A = 0;
volatile int Count_pulses_B = 0;

unsigned long last_time = 0;
float speed_A = 0;
float speed_B = 0;
float target_speed = 100; // 목표 속도 (임의의 값)
float kp = 1.0, ki = 0.5, kd = 0.1;
float error_A = 0, error_B = 0;
float integral_A = 0, integral_B = 0;
float derivative_A = 0, derivative_B = 0;
float last_error_A = 0, last_error_B = 0;

void setup() {
  Serial.begin(9600); // activates the serial communication
  pinMode(Encoder_output_A, INPUT); // sets the Encoder_output_A pin as the input
  pinMode(Encoder_output_B, INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(Encoder_output_A), DC_Motor_Encoder_A, RISING);
  attachInterrupt(digitalPinToInterrupt(Encoder_output_B), DC_Motor_Encoder_B, RISING);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - last_time >= 100) { // 100ms마다 속도 계산 및 제어
    // Calculate speed
    speed_A = Count_pulses_A / 100.0;
    speed_B = Count_pulses_B / 100.0;
    
    // Reset pulse counts
    Count_pulses_A = 0;
    Count_pulses_B = 0;
    
    // PID Control for motor A
    error_A = target_speed - speed_A;
    integral_A += error_A * (current_time - last_time);
    derivative_A = (error_A - last_error_A) / (current_time - last_time);
    float output_A = kp * error_A + ki * integral_A + kd * derivative_A;
    last_error_A = error_A;
    
    // PID Control for motor B
    error_B = target_speed - speed_B;
    integral_B += error_B * (current_time - last_time);
    derivative_B = (error_B - last_error_B) / (current_time - last_time);
    float output_B = kp * error_B + ki * integral_B + kd * derivative_B;
    last_error_B = error_B;
    
    // Update motor speeds
    analogWrite(ENA, constrain(output_A, 0, 255));
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    analogWrite(ENB, constrain(output_B, 0, 255));
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
    // Print speeds for debugging
    Serial.print("Speed A: ");
    Serial.print(speed_A);
    Serial.print(" Speed B: ");
    Serial.println(speed_B);
    
    last_time = current_time;
  }
  
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 's') {
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}

void DC_Motor_Encoder_A() {
  Count_pulses_A++;
}

void DC_Motor_Encoder_B() {
  Count_pulses_B++;
}
