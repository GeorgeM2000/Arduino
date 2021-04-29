const int LEDpins[] = {10,11,12}; // Led pins 



void setup(){
  pinMode(2,OUTPUT);         // Digital pin 2 is connected to the trigger pin
  pinMode(4,INPUT);         // Digital pin 4 is connected to the echo pin
  for(int i = 0; i < 3; i++) {
    pinMode(LEDpins[i],OUTPUT);   // Set the led pins to OUTPUT
  }
}

void loop(){
  long Distance;
  
  Distance = dis(2,4);        // Calculate the distance of the object
  LED_display(Distance);      // Activate leds based on the distance of the object
  delay(500);
}

long dis(int TrigPin, int EchoPin){
  
  // Activation signal -------------
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  // -------------------------------
  
  long Duration = pulseIn(EchoPin, HIGH);
  return microsecondsToCentimeters(Duration);     //
}


// Function to determine what leds need to be activated
void LED_display(long distance){
  if(distance >= 240){        // If the distance is greater than 240 cm, activate one led
    LED_on(LOW,LOW,HIGH);}
  else if(distance > 120){      // If the distance is greater than 120 cm, activate two leds
    LED_on(LOW,HIGH,HIGH);}
  else if(distance < 90){     // If the distance is lower than 90 cm, activate all three leds
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
