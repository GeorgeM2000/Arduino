/* 
  This script is used for a circuit in which i use an ultrasonic sensor to detect the distance from an obstacle.
  Based on the distance of the obstacle, certain leds are activated.

*/


const int LEDpins[] = {10,11,12};                 // Digital pins for the Green, Yellow and Red LED 

void setup(){

   // Digital pin 2 is connected to the trigger pin of the Ultrasonic sensor
   // The trigger pin of the Ultrasonic sensor reads an activation signal transmited from the Arduino
   // Arduino sends an activation signal to trigger pin so digital pin 2 is an output
  pinMode(2,OUTPUT);  

  // Digital pin 4 is connected to the echo pin 
  // The Echo pin of the Ultrasonic sensor takes the information about the distacle of the obstacle                     
  pinMode(4,INPUT);                         
  for(int i = 0; i < 3; i++) {
    pinMode(LEDpins[i],OUTPUT);         // Set the led pins to OUTPUT
  }
}

void loop(){
  long Distance;
  
  Distance = dis(2,4);                    // Calculate the distance of the object
  LED_display(Distance);                // Activate leds based on the distance of the object
  delay(500);
}

long dis(int TrigPin, int EchoPin){
  

  // We use an activation signal to activate the sensor and transmit pulses
  // Activation signal -------------
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  // -------------------------------
  

  // Arduino reads the Echo signal from the sensor through an input digital pin.
  // The Echo signal is a pulse which indicates the time it took for the signal to leave and return from the obstacle
  long Duration = pulseIn(EchoPin, HIGH);             
  return microsecondsToCentimeters(Duration);         
}


// Function to determine how many leds need to be activated
void LED_display(long distance){
  if(distance >= 240){                        // If the distance is greater than 240 cm, activate one led(Green LED)
    LED_on(LOW,LOW,HIGH);}
  else if(distance > 120){                // If the distance is greater than 120 cm, activate two leds(Green and Yellow LED)
    LED_on(LOW,HIGH,HIGH);}
  else if(distance < 90){             // If the distance is lower than 90 cm, activate all three leds(Green, Yellow and Red LED)
    LED_on(HIGH,HIGH,HIGH);}
}

// Function to activate leds
void LED_on(int state1,int state2,int state3){
  digitalWrite(LEDpins[0],state1);
  digitalWrite(LEDpins[1],state2);
  digitalWrite(LEDpins[2],state3);
}


// Function to convert the microseconds passed as an argument to centimeters
long microsecondsToCentimeters(long microsec) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microsec/29/2;
}
