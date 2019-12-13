const int sensorPin = A0;  // pin al cual se conecta la entrada analogica 
// variables de kalman
float varVolt = 1.12184278324081E-05;// varianza determinada por una hoja de excel 
float varProcess = 1e-8;
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorVal = analogRead(sensorPin);     //lectura de valores 
  float voltage = sensorVal * 5.0 / 1023.0;
  // algoritmo de kalman
  Pc = P + varProcess;
  G = Pc/(Pc + varVolt);// ganancia de kalman 
  P = (1-G)*Pc;
  Xp = Xe;
  Zp = Xp;
  Xe = G*(voltage-Zp)+Xp;// la estimacion de kalman para el sensor en cuestion .
 // serialFloatPrint(voltage);
  //serialFloatPrint(Xe);
  Serial.print(voltage*1000);
  Serial.print(' ');
  Serial.println(Xe*1000);
  
  delay(20);
}

// function to print out floats in HEX
void serialFloatPrint(float f) {
  byte * b = (byte *) &f;
  Serial.print("#");
  for(int i=0; i<4; i++) {
    byte b1 = (b[i] >> 4) & 0x0f;
    byte b2 = (b[i] & 0x0f);
    char c1 = (b1 < 10) ? ('0' + b1) : 'A' + b1 - 10;
    char c2 = (b2 < 10) ? ('0' + b2) : 'A' + b2 - 10;
    //Serial.print(String(c1));
    //Serial.print(String(c2));
  }
}
