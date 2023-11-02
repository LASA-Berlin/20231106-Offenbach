#include <DmxSimple.h>
#include <MIDI.h>
#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(8, 9);
MIDI_CREATE_INSTANCE(SoftwareSerial, SoftSerial, MIDI);

// Deklaration der Variablen, Pins und Konstanten:
const int schwelle = 80;
bool spiel_laeuft = false;
bool alarm = false;
unsigned long timerAlarm = 0;
bool gamestart = 0;

int StatusLaser1 = true;
int StatusLaser2 = true;
int StatusLaser3 = true;
int StatusLaser4 = true;
int StatusLaser5 = true;
int StatusLaser6 = true;
int StatusLaser7 = true;
int StatusLaser8 = true;

const int sensor1 = A0;
const int sensor2 = A1;
const int sensor3 = A2;
const int sensor4 = A3;
const int sensor5 = A4;
const int sensor6 = A5;
const int sensor7 = A6;
const int sensor8 = A7;

const int pinLaser1 = 53;
const int pinLaser2 = 51;
const int pinLaser3 = 49;
const int pinLaser4 = 47;
const int pinLaser5 = 45;
const int pinLaser6 = 43;
const int pinLaser7 = 41;
const int pinLaser8 = 39;

const int pin_alarm = 21 const int reset = 5;
const int unscharf = 6;
const int Applaus = 7;
const int resetAntenne = 13;
const int unscharfAntenne = 11;
const int ApplausAntenne = 10;
const int tueren = 22;
const int fussKnopf = 37;  // Bisher noch nicht angeschlossen

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

void chaser() {
  int laser[8] = { 53, 51, 49, 47, 45, 43, 41, 39 };
  int laserState[8] = { StatusLaser1, StatusLaser2, StatusLaser3, StatusLaser4, StatusLaser5, StatusLaser6, StatusLaser7, StatusLaser8 };

  // einen an, kurze warten
  for (int i = 0; i < 8; i++) {
    if (laserState[i] == 0) {
      digitalWrite(laser[i], HIGH);
      MIDI.sendNoteOn(38, 100, 10);
      delay(110);
    }
  }
}

void PlayAlarm() {
  MIDI.sendNoteOn(40, 100, 10);
}

void PlayApplaus() {
  MIDI.sendNoteOn(41, 100, 10);
}

void DMXAlarmOn() {
  DmxSimple.write(33, 0);
  DmxSimple.write(34, 0);
  DmxSimple.write(35, 255);
  DmxSimple.write(36, 255);
  DmxSimple.write(37, 155);  // 155
    digitalWrite(pin_alarm, HIGH);
}

void DMXAlarmOff() {
  DmxSimple.write(33, 255);
  DmxSimple.write(34, 155);
  DmxSimple.write(35, 0);
  DmxSimple.write(36, 0);
  DmxSimple.write(37, 0);  // 155
  digitalWrite(pin_alarm, LOW);
}

void setup() {
  // Shiel und Libary Initialisierung
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  DmxSimple.usePin(4);

  SoftSerial.begin(31250);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Pindeklaration:
  // pins warten auf ein HIGH
  pinMode(reset, INPUT);
  pinMode(unscharf, INPUT);
  pinMode(Applaus, INPUT);
  pinMode(resetAntenne, INPUT);
  pinMode(unscharfAntenne, INPUT);
  pinMode(ApplausAntenne, INPUT);
  pinMode(tueren, OUTPUT);
  pinMode(pinLaser1, OUTPUT);
  pinMode(pinLaser2, OUTPUT);
  pinMode(pinLaser3, OUTPUT);
  pinMode(pinLaser4, OUTPUT);
  pinMode(pinLaser5, OUTPUT);
  pinMode(pinLaser6, OUTPUT);
  pinMode(pinLaser7, OUTPUT);
  pinMode(pinLaser8, OUTPUT);

  // Laser vorbereiten
  AlleLaserAn();
  MIDI.sendNoteOn(40, 0, 10);
  MIDI.sendNoteOn(41, 0, 10);
}

void loop() {
  // wenn Sensor dunkel, passenden Laser aus und alarm an!
  if (StatusLaser1 == true && analogRead(sensor5) < schwelle) {
    StatusLaser1 = false;
    alarm = true;
  }
  if (StatusLaser2 == true && analogRead(sensor4) < schwelle) {
    StatusLaser2 = false;
    alarm = true;
  }
  if (StatusLaser3 == true && analogRead(sensor2) < schwelle) {
    StatusLaser3 = false;
    alarm = true;
  }
  if (StatusLaser4 == true && analogRead(sensor1) < schwelle) {
    StatusLaser4 = false;
    alarm = true;
  }
  if (StatusLaser5 == true && analogRead(sensor3) < schwelle) {
    StatusLaser5 = false;
    alarm = true;
  }
  if (StatusLaser6 == true && analogRead(sensor6) < schwelle) {
    StatusLaser6 = false;
    alarm = true;
  }

  UpdateLaser();  // Hier werden die Laser geschalten, vor allem anderem!

  // haben wir einen Reset? Dann alle Laser wieder an und Alarm aus!å
  // digitalRead(reset) == HIGH ||
  if (digitalRead(resetAntenne) == HIGH) {
    spiel_laeuft = true;
    alarm = false;
    DMXAlarmOff();
    digitalWrite(tueren, LOW);
    if (gamestart == 0)
      chaser();
    gamestart = 1;
    AlleLaserAn();
    UpdateLaser();
  }

  // haben wir einen Alarm OFF? Dann alle Laser aus! und alarm bleibt aus!
  // digitalRead(unscharf) == HIGH ||
  if (digitalRead(unscharfAntenne) == HIGH) {
    alarm = false;
    spiel_laeuft = false;
    AlleLaserAus();
    DMXAlarmOff();
    digitalWrite(tueren, LOW);
    gamestart = 0;
  }

  // Haben wir einen Applaus? Dann PlayApplaus()
  /*if (digitalRead(Applaus) == HIGH || digitalRead(ApplausAntenne) == HIGH) {
    PlayApplaus();
  }*/

  if (alarm == true && spiel_laeuft == true) {
    PlayAlarm();
    DMXAlarmOn();
    alarm = false;
    timerAlarm = millis();
    spiel_laeuft = false;
    digitalWrite(tueren, HIGH);
  }

  unsigned long refTime = millis();
  if ((refTime - timerAlarm) >= 8000) {
    DMXAlarmOff();
  }
}  // loop
