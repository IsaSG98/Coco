#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include<EEPROM.h>
#include "RTClib.h"
   RTC_DS3231 rtc;
   int distancia;
   int lectura;
   float volt,temp;

   NewPing sonar(10,6); //trigger:10  echo:13
   Servo servoMotor;
   LiquidCrystal lcd(12,11,5,4,3,2);
   String daysOfTheWeek[7] = { "Dom", "Lun", "Mart", "Mie", "Jue", "Vie", "Sab" };
   String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
   
   
void setup() {
   
   servoMotor.attach(9);
   lcd.begin(16,2);
   //delay(1000);

   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
 
   // Si se ha perdido la corriente, fijar fecha y hora
   if (rtc.lostPower()) {
      // Fijar a fecha y hora de compilacion
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      
      
   }
  
 }
 void printDate(DateTime date)
{
  lcd.setCursor(0,0);
   lcd.print(date.day(), DEC);
   lcd.print('/');
   lcd.print(date.month(), DEC);
   lcd.print('/');
   lcd.print(date.year(), DEC);
   lcd.print(" (");
   lcd.print(daysOfTheWeek[date.dayOfTheWeek()]);
   lcd.print(") ");
   lcd.setCursor(0,1);
   lcd.print(date.hour(), DEC);
   lcd.print(':');
   lcd.print(date.minute(), DEC);
   //lcd.print(':');
  
}
 
 
void loop() {
   lectura=analogRead(A0);
   volt=(lectura/1024.0)*5.0;
   temp =(volt)*100;
   lcd.setCursor(10,1);
   lcd.print(temp);
   lcd.print("C");
   //delay(1000); si se activa el delay se estabiliza la temperatura
   
 

  
  distancia=sonar.ping_cm();
  Serial.println ( distancia);
  servoMotor.write(0);
  
  if(distancia<=10&& distancia >1){
    
   servoMotor.write(60);
   delay(2000);
   servoMotor.write(0);
   
  }
  
 
  
  delay (100);
  
   // Obtener fecha actual y mostrar por Serial
   DateTime now = rtc.now();
   printDate(now);
 
}
