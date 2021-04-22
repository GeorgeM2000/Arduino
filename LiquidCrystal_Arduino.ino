#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,4,5,6,7);
String Msg = "This is my first LiquidCrystal Program.";
unsigned int stringLength = Msg.length();

void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Hello world!");
}

void loop()
{
  for( int i=0; i<stringLength ; i++ )
  {
    lcd.setCursor(0,1);
    lcd.print(Msg.substring(i));
    lcd.print("                ");
    delay(1000);
  }
}
