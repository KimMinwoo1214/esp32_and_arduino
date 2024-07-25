/*
MIT License

...

*/

#include <Servo.h>

Servo base;
Servo shoulder;
Servo forearm;
Servo upperarm;

int baseAngle = 90;
int shoulderAngle = 90;
int forearmAngle = 90;
int upperarmAngle = 90;

int servoParallelControl(int thePos, Servo &theServo, int speed) {
    int startPos = theServo.read();       // read the current position of the servo we are working with.
    int newPos = startPos;                // newPos holds the position of the servo as it moves
    
    // define where the pos is with respect to the command
    // if the current position is less than the desired, move the position up
    if (startPos < (thePos)) {
        newPos = newPos + 1;               
        theServo.write(newPos);
        delay(speed);
        return 0; // Tell primary program that servo has not reached its position     
    }
    // else if the current position is greater than the desired, move the servo down
    else if (newPos > (thePos)) {
        newPos = newPos - 1;
        theServo.write(newPos);
        delay(speed);
        return 0;  
    }  
    // If the servo is +-1 within the desired range, then tell the main program that the servo has reached the desired position.
    else {
        return 1;
    }  
}

void setup() {
    Serial.begin(115200);
    base.attach(3);
    base.write(baseAngle);
    shoulder.attach(5);
    shoulder.write(shoulderAngle);
    forearm.attach(6);
    forearm.write(forearmAngle);
    upperarm.attach(9);
    upperarm.write(upperarmAngle);
}

int status1 = 0;  // base status
int status2 = 0;
int status3 = 0;
int done = 0;

void loop() {
    // move the base, shoulder, and forearm servos to the desired position
    while(done == 0) {
        status1 = servoParallelControl(120, base, 20);
        status2 = servoParallelControl(120, shoulder, 20);
        status3 = servoParallelControl(120, forearm, 20);

        // Check whether all the joints have reached their positions
        if (status1 == 1 && status2 == 1 && status3 == 1) {
            done = 1; // When done =1, then the loop will stop
        }
    }

    // After reaching the initial positions, move the upperarm servo 5 times
    for (int i = 0; i < 5; i++) {
        int status4 = 0;
        while (status4 == 0) {
            status4 = servoParallelControl(120, upperarm, 20);
        }
        delay(500); // Optional delay to see the position
        status4 = 0;
        while (status4 == 0) {
            status4 = servoParallelControl(90, upperarm, 20);
        }
        delay(500); // Optional delay to see the position
    }
}
