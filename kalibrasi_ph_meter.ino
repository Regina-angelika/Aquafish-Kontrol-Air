float voltage;
float pHValue;
int adcPH;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
adcPH = analogRead(13); //menggunakan pin A0 untuk membaca output sensor pH
voltage = adcPH *5.0/1022;
pHValue = (6.4516*voltage)-5.7742;
Serial.print("sensor ph : ");
Serial.print(pHValue);
Serial.print("sensor ph : ");
Serial.println(pHValue);
delay(1000);
}
