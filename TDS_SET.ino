#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TAMPIL_SERIAL true
#define PIN_SENSOR A0

LiquidCrystal_I2C lcd(0x27,16,2);

int sensorValue=0;
float tdsValue=0;
float voltage=0;

void setup() {
  // put your setup code here, to run once:
  #if TAMPIL_SERIAL
    Serial.begin(9600);
  #endif

  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  sensorValue=analogRead(PIN_SENSOR);
  voltage=sensorValue *3.3/1024.0;
  tdsValue=(133.42*voltage*voltage*voltage - 255.86*voltage*voltage + 857.39*voltage)*0.5;

  #if TAMPIL_SERIAL
    Serial.print("TDS Value= ");
    Serial.print(tdsValue);
    Serial.println(" ppm");
  #endif

  lcd.setCursor(0,0);
  lcd.print("TDS VAL = ");
  lcd.setCursor(10,0);
  lcd.print(tdsValue);
  lcd.setCursor(17,0);
  lcd.print("PPM");
  delay(1000);
}
