const int sensor1 = A13;
const int sensor2 = A12;
const int sensor3 = A14;
const int sensor4 = A10;
const int sensor5 = A9;
const int sensor6 = A15;
const int sensor7 = A11;

void printWithZeros(int t_data) {
  if (t_data < 1000) Serial.print("0");
  if (t_data < 100) Serial.print("0");
  if (t_data < 10) Serial.print("0");
  Serial.print(t_data);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Sensor 1> ");
  printWithZeros(analogRead(sensor1));
  Serial.print(" | Sensor 2 | ");
  printWithZeros(analogRead(sensor2));
  Serial.print(" | Sensor 3 | ");
  printWithZeros(analogRead(sensor3));
  Serial.print(" | Sensor 4 | ");
  printWithZeros(analogRead(sensor4));
  Serial.print(" | Sensor 5 | ");
  printWithZeros(analogRead(sensor5));
  Serial.print(" | Sensor 6 | ");
  printWithZeros(analogRead(sensor6));
  Serial.print(" | Sensor 7 | ");
  printWithZeros(analogRead(sensor7));
  Serial.println();
  delay(500);
}
