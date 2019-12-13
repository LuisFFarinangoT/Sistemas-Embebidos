const float ArduinoVoltage = 3.3; // Voltaje usado
const float ArduinoResolution = ArduinoVoltage / 1024;
const float resistorValue = 10000.0;
int threshold = 3;
int inputPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
}

void loop(){
  int analogValue = 0;
  int oldAnalogValue = 1000;
  float returnVoltage = 0.0;
  float resistance = 0.0;
  double Siemens;
  float TDS = 0.0;

  while (((oldAnalogValue - analogValue) > threshold) || (oldAnalogValue < 50))  {
    oldAnalogValue = analogValue;
    delay(10); // allow ringing to stop
    analogValue = analogRead( inputPin );
  }

  Serial.print("Voltaje = ");
  returnVoltage = analogValue * ArduinoResolution;
  Serial.print(returnVoltage);
  Serial.println(" voltios");
  resistance = ((3.3 * resistorValue) / returnVoltage) - resistorValue;
  Serial.print("Conductividad: ");
  Siemens = 1.0 / (resistance / 1000000);
  Serial.print(Siemens);
  Serial.println(" microSiemens.");
  Serial.print("Podemos estimar una cantidad de disueltos de ");
  TDS = 500 * (Siemens / 100);
  Serial.print(TDS);
  Serial.println(" PPM.");
  if (returnVoltage > 4.9) Serial.println("Are you sure this isn't metal?");
  delay(5000);
}
