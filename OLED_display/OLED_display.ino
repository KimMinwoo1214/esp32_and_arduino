#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

// OLED 디스플레이 설정 (사용하는 디스플레이 모델에 맞게 수정 필요)
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // I2C 방식

void setup(void) {
  u8x8.begin();
  u8x8.setPowerSave(0);
  Serial.begin(9600);
}

void loop(void) {
  if (Serial.available() > 0) {
    String uga = Serial.readStringUntil('\n');
    String numberString = "";

    for (int i = 0; i < uga.length(); i++) {
      if (isDigit(uga.charAt(i))) {
        numberString += uga.charAt(i);
      }
    }
    
    u8x8.clearDisplay(); // 디스플레이 클리어

    if (numberString.length() > 0) {
      int num = numberString.toInt();
      Serial.println(num);
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0, 1, numberString.c_str());  // String을 const char*로 변환하여 출력
    } else {
      Serial.println("No digits found.");
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0, 1, "No digits");
    }

    delay(2000);

  }
}
