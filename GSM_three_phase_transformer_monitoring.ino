#include <Wire.h>
#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial SIM900(9, 10);

const int trigPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor

long duration;
int OilLevel;
int delayTime = 500;

int EarthCurrent;
float SensorReadEarth;

int temp;
float TempSensorPin = A3;
float vout;

const int FirstLoadPin = A0;
const int SecondLoadPin= A1;
const int ThirdLoadPin= A2;
double Voltage = 0;
double VRMS = 0;

double FirstLoadCurrent = 0;
double SecondLoadCurrent = 0;
double ThirdLoadCurrent = 0;

float sensitivity = 0.185;
float LoadSensitivity = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(TempSensorPin,INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
 Serial.begin(9600);
 SIM900.begin(9600);
 delay(100);
Serial.println(" REMOTE TRANSFORMER MONITORING");  
lcd.begin(20,4);
lcd.print("PROJECT WORK");
lcd.setCursor(5,1);
lcd.print("REMOTE");
lcd.setCursor(4,2);
lcd.print("MONITORING");
lcd.setCursor(5,3);
lcd.print("TRANSFORMER");
delay (delayTime);
lcd.clear();
}
void loop() {
  
//temperature//
vout = analogRead(TempSensorPin);
vout = (vout * 500) / 1023;
temp = vout;

//load currents//
Voltage = getVPP();
VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707

FirstLoadCurrent = (VRMS * 1000)/LoadSensitivity;
SecondLoadCurrent = (VRMS * 1000)/LoadSensitivity;
ThirdLoadCurrent = (VRMS * 1000)/LoadSensitivity;


//EARTH CURRENT//
SensorReadEarth = analogRead(A4)*(5.0 / 1023.0);     //We read the sensor output  
EarthCurrent = (SensorReadEarth-2.5)/sensitivity;                  //Calculate the current value for earth

// SENSING OIL LEVEL//
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
OilLevel = duration * 0.034 / 2;

//LCD PRINTING//
lcd.setCursor(0,0);
lcd.print("Line1 current:");
lcd.setCursor(14,0);
lcd.print(FirstLoadCurrent);
lcd.setCursor(19,0);
lcd.print("A");
lcd.setCursor(0,1);
lcd.print("Line2 Current:");
lcd.setCursor(14,1);
lcd.print(SecondLoadCurrent);
lcd.setCursor(19,1);
lcd.print("A");
lcd.setCursor(0,2);
lcd.print("Line3 Current:");
lcd.setCursor(14,2);
lcd.print(ThirdLoadCurrent);
lcd.setCursor(19,2);
lcd.print("A");
lcd.setCursor(0, 3);
lcd.print("Earth Current:");
lcd.setCursor(14, 3);
lcd.print(EarthCurrent,2);
lcd.setCursor(16, 3);
lcd.print("A");
delay(600);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature:");
lcd.setCursor(12,0);
lcd.print(temp);
lcd.setCursor(15,0);
lcd.print("C");
lcd.setCursor(0,1);
lcd.print("Oil Level:");
lcd.setCursor(10,1);
lcd.print(OilLevel);
lcd.setCursor(14,1);
lcd.print("CM");
delay(500);
condition();
}
void sms()
{
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("HIGH TRANSFORMER TEMPERATURE"); // message to send
Serial.println("HIGH TRANSFORMER TEMPERATURE");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms1(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("OIL TANK FULL"); // message to send
Serial.println("OIL TANK FULL");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms2(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("LOW OIL LEVEL"); // message to send
Serial.println("LOW OIL LEVEL");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms3(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("EARTH FAULT CURRENT"); // message to send
Serial.println("EARTH FAULT CURRENT");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms4(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("LINE 1 OVERLOADED"); // message to send
Serial.println("LINE 1 OVERLOADED");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms5(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"+xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("LINE 2 OVERLOADED"); // message to send
Serial.println("LINE 2 OVERLOADED");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void sms6(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"xxxxxxxxxxxx\"");// recipient's mobile number
Serial.println("AT + CMGS = \"xxxxxxxxxxxx\"");// recipient's mobile number
SIM900.println("LINE 3 OVERLOADED"); // message to send
Serial.println("LINE 3 OVERLOADED");
SIM900.println((char)26); // End AT command with a ^Z, ASCII code 26
Serial.println((char)26);
SIM900.println();
}
void condition()
{
  if (temp > 75)
{
lcd_tempPrint();
sms();
 delay(300);
  }
if (OilLevel > 800)
{
 lcd_oilLevelFULLPrint();
 sms1();
 delay(1000);
  }else if (OilLevel < 300)
{lcd_oilLevelLOWPrint();
 sms2();
 delay(300);
  }
if (EarthCurrent > 1 )
{
lcd_EarthCurrentPrint();
sms3();
delay (300);
  }

if (FirstLoadCurrent < 2)
  {
    lcd_FirstLoadCurrentPrint();
    sms4();
    delay(200);
    }
if (SecondLoadCurrent < 2)
  {
    lcd_SecondLoadCurrentPrint();
    sms5();
    delay(200);
    }
if (ThirdLoadCurrent < 2)
  {
    lcd_ThirdLoadCurrentPrint();
    sms6();
    delay(200);
    } 
}
// LCD PRINTING//
void lcd_oilLevelFULLPrint()
{
lcd.clear();
lcd.setCursor(1,1);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL TANK FULL");  
 
}
void lcd_oilLevelLOWPrint()
{
lcd.clear();
lcd.setCursor(0,2);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("OIL LEVEL LOW");  
}
void lcd_tempPrint()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.clear();                                  //if condition temp for it to print.
lcd.print("HIGH TEMPERATURE");     
}
void lcd_EarthCurrentPrint()
{
 lcd.clear();
 lcd.setCursor(1, 1);                         // if condition for it print earth current.
 lcd.print("EARTH FAULT CURRENT");
}
void lcd_FirstLoadCurrentPrint(){
 lcd.clear();
 lcd.setCursor(1, 1);                         // if condition for it print earth current.
 lcd.print("LINE 1 OVERLOADED");
  }
void lcd_SecondLoadCurrentPrint(){
 lcd.clear();
 lcd.setCursor(1, 1);                         // if condition for it print earth current.
 lcd.print("LINE 2 OVERLOADED");
  }
void lcd_ThirdLoadCurrentPrint(){
 lcd.clear();
 lcd.setCursor(1, 1);                         // if condition for it print earth current.
 lcd.print("LINE 3 OVERLOADED");
  }
float getVPP()
{
  float result;
  int FirstLoadValue;             //value read from the sensor
  int SecondLoadValue;
  int ThirdLoadValue;
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       FirstLoadValue = analogRead(FirstLoadPin);
       SecondLoadValue=analogRead(SecondLoadPin);
       ThirdLoadValue=analogRead(SecondLoadPin);
       // see if you have a new maxValue
       if (FirstLoadValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = FirstLoadValue;
       }
       if (FirstLoadValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = FirstLoadValue;
       }
       if (SecondLoadValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = SecondLoadValue;
       }
       if (SecondLoadValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = SecondLoadValue;        
        if (FirstLoadValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = FirstLoadValue;
       }
       if (FirstLoadValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = FirstLoadValue;
       }
   }
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;}
 }
