int valor = 0;
int control = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  valor = (analogRead(A1) * 10) / 1023;
  Serial.write(valor);
 delay(200);
///Serial.println(valor);
}
