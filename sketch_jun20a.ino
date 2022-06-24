#include <LiquidCrystal.h>

//PIN VARIABLES
int motorPin = 2;
int sensorPin = A0;

//VARIABLES
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int sensorValue; 
int mode = 0;

void setup() {

  //set the motor control pins as outputs
  pinMode(motorPin, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);                       
}

void loop() {
    moistureSensor();
    state();
}


void moistureSensor()
{
  sensorValue = analogRead(sensorPin);
  Serial.println("Analog Value : ");
  Serial.println(sensorValue);
  
  if (sensorValue < 400)
  {
    mode = 1;
  }
  else if (sensorValue > 600){
    mode = 2;
  }
  else{
    mode = 0;
  }
}

void state() 
{
  switch (mode){
   case 0: //standby
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Please Stand by");
    break;
   case 1: // Dry
    digitalWrite(motorPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil is dry!");
    lcd.setCursor(0, 1);
    lcd.print("Turning on water!");
    break;
   case 2: // Wet
    lcd.clear();
    digitalWrite(motorPin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Soil is good!");
    lcd.setCursor(0, 1);
    lcd.print("Turning off water!");
    break;
  }
 }
