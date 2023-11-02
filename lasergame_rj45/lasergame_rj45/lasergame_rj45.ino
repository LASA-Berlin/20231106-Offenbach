#include <Conceptinetics.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

// Variablen und Konstanten Objekte
const int Schwelle = 200;
bool spiel_laeuft = false;
bool alarm = false;
bool gamestart = 0;
unsigned long timerAlarm = 0;

const int MAX_CHANNELS = 50;
const int PIN_DMX = 2;

int StatusLaser1 = 255;
int StatusLaser2 = 255;
int StatusLaser3 = 255;
int StatusLaser4 = 255;
int StatusLaser5 = 255;
int StatusLaser6 = 255;
int StatusLaser7 = 255;

const int sensor1 = A13;
const int sensor2 = A12;
const int sensor3 = A14;
const int sensor4 = A10;
const int sensor5 = A9;
const int sensor6 = A15;
const int sensor7 = A11;

const int pin_alarm = 21;
const int resetAntenne = 6;
const int unscharfAntenne = 7;
const int ApplausAntenne = 5;

SoftwareSerial SoftSerial(8, 9);
MIDI_CREATE_INSTANCE(SoftwareSerial, SoftSerial, MIDI);

DMX_Master dmx_master(MAX_CHANNELS, PIN_DMX);

// Funktionen
void AlleLaserAn() {
  StatusLaser1 = 255;
  StatusLaser2 = 255;
  StatusLaser3 = 255;
  StatusLaser4 = 255;
  StatusLaser5 = 255;
  StatusLaser6 = 255;
  StatusLaser7 = 255;
}

void AlleLaserAus() {
  StatusLaser1 = 0;
  StatusLaser2 = 0;
  StatusLaser3 = 0;
  StatusLaser4 = 0;
  StatusLaser5 = 0;
  StatusLaser6 = 0;
  StatusLaser7 = 0;
}

void UpdateLaser() {
  dmx_master.setChannelValue(1, StatusLaser1);
  dmx_master.setChannelValue(2, StatusLaser2);
  dmx_master.setChannelValue(3, StatusLaser3);
  dmx_master.setChannelValue(4, StatusLaser4);
  dmx_master.setChannelValue(5, StatusLaser5);
  dmx_master.setChannelValue(6, StatusLaser6);
  dmx_master.setChannelValue(7, StatusLaser7);
}

void PlayAlarm() {
  MIDI.sendNoteOn(40, 100, 10);
}

void PlayApplaus() {
  MIDI.sendNoteOn(41, 100, 10);
}

void DMXAlarmOn() {
  dmx_master.setChannelValue(33, 0);    // r
  dmx_master.setChannelValue(34, 0);    // g
  dmx_master.setChannelValue(35, 255);  // b
  dmx_master.setChannelValue(36, 255);  // dimmer
  dmx_master.setChannelValue(37, 155);  // strobo
  digitalWrite(pin_alarm, HIGH);
}

void DMXAlarmOff() {
  dmx_master.setChannelValue(33, 0);    // r
  dmx_master.setChannelValue(34, 0);    // g
  dmx_master.setChannelValue(35, 255);  // b
  dmx_master.setChannelValue(36, 0);    // dimmer
  dmx_master.setChannelValue(37, 155);  // strobo
  digitalWrite(pin_alarm, LOW);
}

void setup() {
  // Shiel und Libary Initialisierung
  dmx_master.enable();

  SoftSerial.begin(31250);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Pindeklaration:
  pinMode(resetAntenne, INPUT);
  pinMode(unscharfAntenne, INPUT);
  pinMode(ApplausAntenne, INPUT);

  // Laser vorbereiten
  AlleLaserAn();
  // Alle 'Overhead' DMX-Kanaele anschalten

  MIDI.sendNoteOn(40, 0, 10);
  MIDI.sendNoteOn(41, 0, 10);
}

void loop() {
  // wenn Sensor dunkel, passenden Laser aus und alarm an!
  if (StatusLaser1 == 255 && analogRead(sensor1) < Schwelle) {
    StatusLaser1 = 0;
    alarm = true;
  }
  if (StatusLaser2 == 255 && analogRead(sensor2) < Schwelle) {
    StatusLaser2 = 0;
    alarm = true;
  }
  if (StatusLaser3 == 255 && analogRead(sensor3) < Schwelle) {
    StatusLaser3 = 0;
    alarm = true;
  }
  if (StatusLaser4 == 255 && analogRead(sensor4) < Schwelle) {
    StatusLaser4 = 0;
    alarm = true;
  }
  if (StatusLaser5 == 255 && analogRead(sensor5) < Schwelle) {
    StatusLaser5 = 0;
    alarm = true;
  }
  if (StatusLaser6 == 255 && analogRead(sensor6) < Schwelle) {
    StatusLaser6 = 0;
    alarm = true;
  }

  UpdateLaser();  // Hier werden die Laser geschalten, vor allem anderem!

  // haben wir einen Reset? Dann alle Laser wieder an und Alarm aus!å
  // digitalRead(reset) == HIGH ||
  if (digitalRead(resetAntenne) == HIGH) {
    spiel_laeuft = true;
    alarm = false;
    DMXAlarmOff();
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
    gamestart = 0;
  }

  // Haben wir einen Applaus? Dann PlayApplaus()
  // digitalRead(Applaus) == HIGH ||
  if (digitalRead(ApplausAntenne) == HIGH) {
    PlayApplaus();
  }

  if (alarm == true && spiel_laeuft == true) {
    PlayAlarm();
    DMXAlarmOn();
    alarm = false;
    timerAlarm = millis();
    spiel_laeuft = false;
  }

  unsigned long refTime = millis();
  if ((refTime - timerAlarm) >= 8000) {
    DMXAlarmOff();
  }
}  // loop
