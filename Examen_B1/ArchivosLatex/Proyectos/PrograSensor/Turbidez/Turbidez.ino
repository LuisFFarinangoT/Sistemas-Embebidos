float voltaje ;
float NTU;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int  sensorVal = analogRead(A0);
  voltaje = sensorVal * (3.3 / 1023.0);
  //y = 174.96x2 - 1357.1x + 2630.5
  //285.48x2 - 2285.5x + 4574.8

  NTU = (float)(285.48 * pow(voltaje, 2)) - (float)2285.5 * voltaje + (float)4574.8;
  //NTU=(float)(-1120.4*pow(voltaje,2))+(float)5742.3*voltaje-(float)4352.9;
  float NTUC = NTU / 1000.00;
  Serial.print("Voltaje: ");
  Serial.print(voltaje);
  Serial.print(" | Turbidez :");
  Serial.print(NTUC);
  Serial.println(" NTU");
  delay(500);
}
