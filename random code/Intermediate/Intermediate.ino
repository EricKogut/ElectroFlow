const int transistorPin = 10;    // connected to the base of the transistor

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int flowPin = 2;    //This is the input pin on the Arduino
double flowRate;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.  


 void setup() {
   // set  the transistor pin as output:
   pinMode(transistorPin, OUTPUT);
   Serial.begin(9600);
   lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light

  pinMode(flowPin, INPUT);           //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"  
  Serial.begin(9600);  //Start Serial
  
 }
 
 void loop() {
  // put your main code here, to run repeatedly:  
  count = 0;      // Reset the counter so we start counting from 0 again
  interrupts();   //Enables interrupts on the Arduino
  delay (10);   //Wait 0.1 second 
  noInterrupts(); //Disable the interrupts on the Arduino
  
  //Start the math
  flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL 
  flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute

  Serial.println(flowRate);         //Print the variable flowRate to Serial
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
  delay(5 ); 

 }

 
void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}
