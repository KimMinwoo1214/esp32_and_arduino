#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

// OLED 디스플레이 설정 (사용하는 디스플레이 모델에 맞게 수정 필요)
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // I2C 방식

#define pin_Trig 7
#define pin_Echo 8
#define pin_Speaker 9

void setup() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  Serial.begin(9600);
  pinMode(pin_Trig, OUTPUT);
  pinMode(pin_Echo, INPUT);
  pinMode(pin_Speaker, OUTPUT);
}

void loop() {
  long duration, distance;

  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);

  duration = pulseIn(pin_Echo, HIGH);

  distance = (duration * 0.0343) / 2;

  char displayChar[4];
  String temp_str = String(distance);
  temp_str.toCharArray(displayChar, 4);

  u8x8.clearDisplay(); // 디스플레이 클리어
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0, 1, displayChar);  // String을 const char*로 변환하여 출력

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 5){
    tone(pin_Speaker, 262);
  }
  else if (distance <= 10) {
    tone(pin_Speaker, 294);
  }
  else if (distance <= 15) {
    tone(pin_Speaker, 294);
  } 
  else{
    noTone(pin_Speaker);  
  }

  delay(100);
}
