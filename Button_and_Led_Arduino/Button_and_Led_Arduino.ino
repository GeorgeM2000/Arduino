/* 
  In this circuit, i use a button, a led and a pull up resistor.
  When the button is pressed, the led is set to high voltage.
  When the button is not pressed, the led is set to low voltage.
*/

const int LED = 7;                    // Set the led to pin 7
const int BUTTON_PIN = 2;             // Set the button to pin 2

void setup() {
  pinMode(LED,OUTPUT);              // Set the digital pin LED to output
  pinMode(BUTTON_PIN,INPUT);       // Set the digital pin BUTTON_PIN to input
}

void loop() {

  if(digitalRead(BUTTON_PIN)==LOW){             // If the button is pressed
    digitalWrite(LED,HIGH);                     // Turn on the led
  } 
  else if(digitalRead(BUTTON_PIN)==HIGH) {      // If the button is not pressed
    digitalWrite(LED,LOW);                      // Turn off the led
  }
}
