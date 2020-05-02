const int transistorPin = 10;    // connected to the base of the transistor

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

 void setup() {
   // set  the transistor pin as output:
   pinMode(transistorPin, OUTPUT);
   Serial.begin(9600);
   lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light
 }
 
 void loop() {
   // read the potentiometer:
   int sensorValue = analogRead(A1);
   // map the sensor value to a range from 0 - 255:
   Serial.print(sensorValue/25);
   Serial.print("\n");
   int outputValue = map(sensorValue, 0, 1023, 0, 255);
   // use that to control the transistor:
   analogWrite(transistorPin, outputValue);
   //Write your code
  lcd.clear();
  lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
  lcd.print((outputValue/25));
  delay(10); 
 }
