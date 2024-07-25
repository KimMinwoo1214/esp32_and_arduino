/*
MIT License

Copyright (c) 2024 JD edu. http://jdedu.kr author: conner.jeong@gmail.com
     
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
     
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
     
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN TH
SOFTWARE.*/

/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

unsigned long timer = 0;
int stepCount = 0;
const float STEP_THRESHOLD = 1.0; // 가속도 변화 임계값 (1g = 9.81 m/s²)
bool stepDetected = false;
float lastAccelMag = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status != 0){ 
    // stop everything if could not connect to MPU6050
    delay(1000);
    status = mpu.begin();
  }
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, true); // 자이로 및 가속도계 오프셋 계산
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();

  if (millis() - timer > 200) { // print data every 200 ms
    detectStep();
    printData();
    timer = millis();
  }
}

void detectStep() {
  // 가속도 크기 계산
  float accelX = mpu.getAccX();
  float accelY = mpu.getAccY();
  float accelZ = mpu.getAccZ();
  float accelMag = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  // 임계값을 초과하는 가속도 변화 감지
  if (abs(accelMag - lastAccelMag) > STEP_THRESHOLD) {
    if (!stepDetected) {
      stepCount++;
      stepDetected = true;
    }
  } else {
    stepDetected = false;
  }
  
  lastAccelMag = accelMag;
}

void printData() {
  Serial.print("STEP COUNT: ");
  Serial.println(stepCount);
  
  Serial.print("ACCELERO  X: "); Serial.print(mpu.getAccX());
  Serial.print("\tY: "); Serial.print(mpu.getAccY());
  Serial.print("\tZ: "); Serial.println(mpu.getAccZ());
  
  Serial.print(F("GYRO      X: ")); Serial.print(mpu.getGyroX());
  Serial.print("\tY: "); Serial.print(mpu.getGyroY());
  Serial.print("\tZ: "); Serial.println(mpu.getGyroZ());
  
  Serial.print(F("ACC ANGLE X: ")); Serial.print(mpu.getAccAngleX());
  Serial.print("\tY: "); Serial.println(mpu.getAccAngleY());
  
  Serial.print(F("ANGLE     X: ")); Serial.print(mpu.getAngleX());
  Serial.print("\tY: "); Serial.print(mpu.getAngleY());
  Serial.print("\tZ: "); Serial.println(mpu.getAngleZ());

  Serial.println(F("=====================================================\n"));
}
