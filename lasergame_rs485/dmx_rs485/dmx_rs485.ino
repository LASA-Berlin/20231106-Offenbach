#include <Conceptinetics.h>

const int MAX_CHANNELS = 50;
const int PIN_DMX = 2;
const int FULL_POWER = 255;
const int ZERO_POWER = 0;
int startChannel = 1;
int endChannel = 3;

DMX_Master dmx_master(MAX_CHANNELS, PIN_DMX);

void DMXAlarmOn() {
  DmxSimple.write(33, 0);
  DmxSimple.write(34, 0);
  DmxSimple.write(35, 255);
  DmxSimple.write(36, 255);
  DmxSimple.write(37, 0);  // 155
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
  dmx_master.enable();
}

void loop() {
  DMXAlarmOn();
  delay(1500);
  DMXAlarmOn();
  delay(1500);
}
