/* 
  This script is used for a circuit in which i use a liquid crystal display.
  When the program starts, a message is printed on the display and remains static.
  A second message is printed throughout the execution of the program.
*/

#include <LiquidCrystal.h>

// Create a LiquidCrystalObject
LiquidCrystal lcd(11,12,4,5,6,7);

String msg = "This is my first program using LiquidCrystal.";
int msgLength = msg.length();

void setup()
{
  lcd.begin(16,2);                  // Specify how large the screen is
  lcd.setCursor(0,0);              // Set the coordinates at the first column of the first row
  lcd.print("Hello Everyone!");   // Write to the LCD screen
}

void loop()
{
  for(int i=0;i<msgLength;i++)
  {
    lcd.setCursor(0,1);                // Set the coordinates at the first column of the second row
    lcd.print(msg.substring(i));      // Write to the LCD screen
    delay(1000);                     // Wait 1 sec
  }
}
