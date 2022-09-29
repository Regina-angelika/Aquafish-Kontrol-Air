#include "Arduino.h"
#include "LMIC-node.h"
#include "PubSubClient.h"
#include "WiFi.h"
#include "Adafruit_Sensor.h"
#include "TheThingsNetwork.h"
#include "heltec.h"
#include "stdlib.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "DHT.h"

#define TOKEN               "70B3D57ED00541EE"
#define THINGSBOARD_SERVER  "thingsboard.cloud"

const char *ssid="reginaangelika73";
const char *pass="@R0709Ayu";

const uint8_t payloadBufferLength = 8;    // Adjust to fit max payload length

//sensor DS18B20 diletakkan di pin 13
#define ONE_WIRE_BUS 23
 
// settingsensor suhu
OneWire oneWire(ONE_WIRE_BUS);
OneWire ds(23);
DallasTemperature sensorTemperature(&ds);

//setting untuk tds
#define TdsSensorPin 36
#define VREF 3.3 // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point
int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;

//setting PH
float calibration = 25; //change this value to calibrate
const int analogInPin = 37; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
float phValue=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorTemperature.requestTemperatures();
   float suhu = (float)(sensorTemperature.getTempCByIndex(0))+ 150;
   Serial.print("Suhu=");
   Serial.println(suhu);

  //hitung tds
  static unsigned long analogSampleTimepoint = millis();
  if(millis()-analogSampleTimepoint > 40U) //every 40 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin); //read the analog value and store into the buffer 5 www.keyestudio.com
    analogBufferIndex++;
    if(analogBufferIndex == SCOUNT)
      analogBufferIndex = 0;
  }
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 800U)
  {
    printTimepoint = millis();
    for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
      analogBufferTemp[copyIndex]= analogBuffer[copyIndex];

    averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF/4096.0; // read the analog value more stable by the median filtering algorithm,and convert to voltage value
    float compensationCoefficient=1.0+0.02*(temperature-25.0); //temperature compensation formula: fFinalResult(25^C) =fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge=averageVoltage/compensationCoefficient;

    //temperature compensation
    tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge +857.39*compensationVolatge)*0.5; //convert voltage value to tds value
}
