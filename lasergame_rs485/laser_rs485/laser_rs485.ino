const int pinLaser1 = 53;
const int pinLaser2 = 51;
const int pinLaser3 = 49;
const int pinLaser4 = 47;
const int pinLaser5 = 45;
const int pinLaser6 = 43;
const int pinLaser7 = 41;
const int pinLaser8 = 39;

void AlleLaserAn() {
  StatusLaser1 = true;
  StatusLaser2 = true;
  StatusLaser3 = true;
  StatusLaser4 = true;
  StatusLaser5 = true;
  StatusLaser6 = true;
  StatusLaser7 = true;
  StatusLaser8 = true;
}

void AlleLaserAus() {
  StatusLaser1 = false;
  StatusLaser2 = false;
  StatusLaser3 = false;
  StatusLaser4 = false;
  StatusLaser5 = false;
  StatusLaser6 = false;
  StatusLaser7 = false;
  StatusLaser8 = false;
}

void UpdateLaser() {
  digitalWrite(pinLaser1, StatusLaser1);
  digitalWrite(pinLaser2, StatusLaser2);
  digitalWrite(pinLaser3, StatusLaser3);
  digitalWrite(pinLaser4, StatusLaser4);
  digitalWrite(pinLaser5, StatusLaser5);
  digitalWrite(pinLaser6, StatusLaser6);
  digitalWrite(pinLaser7, StatusLaser7);
  digitalWrite(pinLaser8, StatusLaser8);
}

void setup() {
  pinMode(pinLaser1, OUTPUT);
  pinMode(pinLaser2, OUTPUT);
  pinMode(pinLaser3, OUTPUT);
  pinMode(pinLaser4, OUTPUT);
  pinMode(pinLaser5, OUTPUT);
  pinMode(pinLaser6, OUTPUT);
  pinMode(pinLaser7, OUTPUT);
  pinMode(pinLaser8, OUTPUT);
}

void loop() {
  AlleLaserAn();
  UpdateLaser();
  delay(1500);
  AlleLaserAus();
  UpdateLaser();
  deölay(1500);
}
