#include "DFRobot_PH.h" //library yang diinstal seperti instruksi diatas
#include <OneWire.h>  //library untuk pembacaan sensor ds18b20
#include <DallasTemperature.h> 
#include <LiquidCrystal_PCF8574.h> 
#include <Wire.h> 
 
LiquidCrystal_PCF8574 lcd(0x27);
 
#define sensor_ds18b20 2 //pada pin 2 untuk sensor ds18b20
 
OneWire oneWire(sensor_ds18b20);
 
DallasTemperature sensors(&oneWire); //penggunaan interface 1 wire untuk pengaksesan
 
int sensorPin = A0;//pembacaan sensor ph menggunakan ADC
 
float tegangan,nilaiph,suhu;
DFRobot_PH ph;
 
void setup()
{
   Serial.begin(9600);  //serial monitor
    ph.begin(); //mulai untuk pembacaan sensor ph meter
    sensors.begin(); //mulai untuk pembacaan sensor ds18b20
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.setCursor(0,0);
    lcd.print("TRIAL PH METER");
    lcd.setCursor(0,1);
    lcd.print("nyebarilmu.com");
    delay(2000);
    lcd.clear();
}
 
void loop()
{
  sensors.requestTemperatures(); 
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        tegangan = analogRead(sensorPin)/1024.0*5000; //mengubah tegangan analog menjadi digital dan menjadi tegangan
        suhu = sensors.getTempCByIndex(00);
        nilaiph = ph.readPH(tegangan,suhu);  //konversi tegangan menjadi ph meter dengan kompensasi suhu
        Serial.print("Celsius temperature: ");
        Serial.print(suhu,1); //nilai pembacaan suhu
        Serial.print("°C  pH:");
        Serial.println(nilaiph,2); //nilai pembacaan ph meter
 
        lcd.setCursor(0,0);
        lcd.print("Suhu:");
        lcd.setCursor(5,0);
        lcd.print(suhu,1);
        lcd.print((char)223); //derajat
 
        lcd.setCursor(0,1);
        lcd.print("PH :");
        lcd.setCursor(4,0);
        lcd.print(nilaiph,2);
 
        lcd.setCursor(10,1);
        if(nilaiph ==7) lcd.print("Normal");
        if(nilaiph <7) lcd.print("Asam  ");
        if(nilaiph >7) lcd.print("Basa  ");
    }
    ph.calibration(tegangan,suhu); 
}
