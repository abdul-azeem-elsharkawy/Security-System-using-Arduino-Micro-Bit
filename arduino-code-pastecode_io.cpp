#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define alarmPin 2
#define accessPin 12
#define redLED 3
#define greenLED 13

LiquidCrystal_I2C lcd_1(32, 16, 2);
int trails = 3;
String password = "2203"; 
String enteredPass = "";
byte columnPins[] = {7,6,5,4};
byte rowPins[] = {11,10,9,8};
byte numOfColumns = 4;
byte numOfRows = 4;
char keys [4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, columnPins, numOfRows, numOfColumns);
String pressedKey = "";
void setup() 
{ 
  pinMode(alarmPin, OUTPUT);
  pinMode(accessPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  lcd_1.init();
  lcd_1.setCursor(0, 0);
  lcd_1.backlight();
  lcd_1.display();
  lcd_1.print("Enter Password:");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Your Trials ");
  lcd_1.setCursor(12, 1);
  lcd_1.print(trails);
  delay(3000);
  lcd_1.clear();
}

void loop() 
{  
  pressedKey = myKeypad.getKey();
  if (pressedKey)
  { 
    if (pressedKey == "#")
    {
      pressedKey = "";
      if (password == enteredPass)
      {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Access Granted!");
        digitalWrite(greenLED, HIGH);
        while (1)
          digitalWrite(accessPin, HIGH);
      }
      else
      {
        trails--;
        enteredPass = "";
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Wrong Password!");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Your Trials ");
        lcd_1.setCursor(12, 1);
        lcd_1.print(trails);
        delay(2000);
        
        if (trails == 0)
        {
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print("System Locked!");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Calling 911");
          while (1)
          {
            digitalWrite(alarmPin, HIGH);
            digitalWrite(redLED, HIGH);
            delay(500);
          }
        }
        lcd_1.clear();
      }
    }
  
    if (enteredPass.length() < 4)
    {
      enteredPass += pressedKey;
      lcd_1.setCursor(enteredPass.length()-1, 0);
      lcd_1.print(pressedKey);
    }
  }
}
