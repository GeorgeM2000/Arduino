const int LED = 7;
const int BUTTON_PIN = 2;

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
}

void loop() {
  if(digitalRead(BUTTON_PIN)==LOW){
    digitalWrite(LED,HIGH);
  } 
  else if(digitalRead(BUTTON_PIN)==HIGH) {  
    digitalWrite(LED,LOW);
  }
}
