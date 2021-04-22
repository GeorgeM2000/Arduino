const byte LED = 7;
const byte BUTTON_PIN = 2;
volatile byte state = LOW;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ActivateLED, CHANGE);
}

void loop() {
  digitalWrite(LED, state);
}

void ActivateLED(){
  state = !state;
}
