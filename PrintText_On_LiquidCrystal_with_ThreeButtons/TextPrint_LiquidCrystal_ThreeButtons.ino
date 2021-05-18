/*
   This script is used for a circuit in which i use a liquidCrystal and three buttons.
   When the first button is pressed text appears on the screen. The text is stored in 
   the variable button1Text. The same thing happens for the other two buttons but with
   different text. When each button is pressed, interrupts are triggered and a function
   is called.
 */

#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>
#include <LiquidCrystal.h>

const int Contrast = 75;                  // The contrast of the screen
const int button1 = 2;                    // Button 1 pin
const int button2 = 3;                    // Button 2 pin
const int button3 = 10;                   // Button 3 pin
int button1State = 0;
int button2State = 0;
int button3State = 0;

// Create a LiquidCrystalObject
LiquidCrystal lcd(11,12,4,5,6,7);

String button1Text = "GEORGE";
String button2Text = "MATLHS";
String button3Text = "2000";


void setup()
{
    analogWrite(8, Contrast);     // Set the contrast of the LCD screen
    
    lcd.begin(16,2);    // Specify how large the screen is
    attachInterrupt(digitalPinToInterrupt(button1), buttonForName, CHANGE);                  // Attach an interrupt to button 1 
    attachInterrupt(digitalPinToInterrupt(button2), buttonForSurname, CHANGE);               // Attach an interrupt to button 2
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(button3), buttonForAM , CHANGE); // Attach a pin change interrupt to button 3

}

void loop()
{
  // If button 1 state changes
  if(button1State) {
    lcd.setCursor(0,0);
    lcd.print(button1Text);         // Print the text to the screen
    delay(2000);                    // Delay 2 sec
    lcd.clear();                    // Clear the screen
    button1State = 0;               
  }
  // If button 2 state changes
  else if(button2State){
    lcd.setCursor(0,0);
    lcd.print(button2Text);         // Print the text to the screen
    delay(2000);                    // Delay 2 sec
    lcd.clear();                    // Clear the screen
    button2State = 0;               
  }
  // If button 3 state changes
  else if(button3State){
    lcd.setCursor(0,0);
    lcd.print(button3Text);         // Print the text to the screen
    delay(2000);                    // Delay 2 sec
    lcd.clear();                    // Clear the screen
    button2State = 0;
  }
  
}

// Interrupt functions ------------------------------
void buttonForName(){
  button1State = !button1State;
}

void buttonForSurname(){
  button2State = !button2State;
}

void buttonForAM(){
  button3State = !button3State;
}
