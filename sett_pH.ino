int pH_value;
float Voltage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pH_value = analogRead(A0);
  Voltage = pH_value * (3.3/1023.0);
  Serial.println(Voltage);
  delay(500);
}
