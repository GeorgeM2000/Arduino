/*
  In this circuit, i use a button, a led, a pull up resistor and i generate interrupts.
  When a transition occurs, that is, we transition from LOW voltage to HIGH and the other way around, the function ActivateLED is called.
  When this function is called the state variable changes, therefore the value of the led changes.
*/

const byte LED = 7;             // Set the led to pin 7
const byte BUTTON_PIN = 2;      // Set the button to pin 2
volatile byte state = LOW;      // Initialize a state variable to LOW

void setup() {
  pinMode(LED, OUTPUT);                                                              // Set the led pin to output
  pinMode(BUTTON_PIN, INPUT);                                                       // Set the button pin to input
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ActivateLED, CHANGE);          // Use the attchInterrupt function to generate interrupts
}

void loop() {
  digitalWrite(LED, state);                       // Set the the led to the value of the state variable
}

void ActivateLED(){
  state = !state;                               // Invert the state variable
}
