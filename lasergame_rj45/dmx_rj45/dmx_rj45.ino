#include <Conceptinetics.h>

const int MAX_CHANNELS = 50;
const int PIN_DMX = 2;
const int FULL_POWER = 255;
const int ZERO_POWER = 0;
int startChannel = 1;
int endChannel = 3;

DMX_Master dmx_master(MAX_CHANNELS, PIN_DMX);

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
  dmx_master.enable();
}

void loop() {
  dmx_master.setChannelRange(1, 6, FULL_POWER);
  dmx_master.setChannelValue(5, FULL_POWER);
  DMXAlarmOn();
  delay(1500);
  dmx_master.setChannelRange(1, 6, ZERO_POWER);
  dmx_master.setChannelValue(5, ZERO_POWER);
  DMXAlarmOn();
  delay(1500);
}
