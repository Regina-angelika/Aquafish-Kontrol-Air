 #include <OneWire.h>
#include <DallasTemperature.h>

#define TAMPIL_SERIAL true
#define PIN_SENSOR 36

int sensorValue=0;
float tdsValue=0;
float voltage=0;

void setup() {
  // put your setup code here, to run once:
 // #if TAMPIL_SERIAL
    Serial.begin(9600);
 // #endif
}
 
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.clear();
  sensorValue=analogRead(PIN_SENSOR);
  voltage=sensorValue *3.3/1024.0;
  tdsValue=(133.42*voltage*voltage*voltage - 255.86*voltage*voltage + 857.39*voltage)*0.5;

 /* #if TAMPIL_SERIAL
    Serial.print("TDS Value= ");
    Serial.print(tdsValue);
    Serial.println(" ppm");
  #endif
*/
  //Serial.setCursor(0,0);
  Serial.print("TDS VAL = ");
  //Serial.setCursor(10,0);
  Serial.print(tdsValue);
 // Serial.setCursor(17,0);
  Serial.println(" PPM");
  delay(5000);
}
