/* 
  This script is used for a circuit in which i use a servo motor.
  The servo motor moves from 0 degrees to 180 and the other way around.
*/

#include <Servo.h>

// Initialize Servo object
Servo myServo;  


// Servo initial position
int pos = 0;   

void setup() {
  myServo.attach(9);      // Attach myServo object to digital pin 9
}

void loop() {
  for (pos=0; pos<=180; pos+=1) { // Servo goes from 0 degrees to 180 degrees
    myServo.write(pos);     // Servo goes to position specified in variable pos
    delay(20);      // Wait 20ms
  }
  for (pos=180; pos>=0; pos-=1) { // Servo goes from 180 degrees to 0 degrees
    myServo.write(pos);     // Servo goes to position specified in variable pos
    delay(20);      // Waits 20ms
  }
}
