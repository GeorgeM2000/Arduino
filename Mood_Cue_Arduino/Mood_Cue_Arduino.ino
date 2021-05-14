/*
 * This script is used for a circuit in which i use a servo motor and a potensiometer.
 * Every time you use the potensiometer, as you turn the knob, you change the ratio of 
 * the voltage divider between the middle pin and power. I convert the analog input value
 * into a value that can be used to set the position of the servo motor. So as you turn 
 * the knob the servo motor is moved.
 */


// Include Servo library
#include <Servo.h>

// Create a Servo instance 
Servo myServo;


int const potPin = A0;        // The pin the potentiometer is attached to
int potVal;                   // A value to hold the analog input
int angle;                    // The angle at which the Servo will move to



void setup() {
  myServo.attach(9);          // Attach the Servo to pin 9
  Serial.begin(9600);         // Include a Serial connection
}

void loop() {
  potVal = analogRead(potPin);            // Read the analog input and store it in potVal

  // Print analog input
  Serial.print("potVal : ");
  Serial.print(potVal);
  
  angle = map(potVal, 0, 1023, 0, 179);   // Create a usable value for the Servo from the analog input and store it in angle

  // Print the angle
  Serial.print("angle : ");
  Serial.print(angle);

  
  myServo.write(angle);                   // Move the servo motor to the angle specified at the variable angle
  delay(15);                              // Put a delay so that the Servo has time to move to the position
  
}
