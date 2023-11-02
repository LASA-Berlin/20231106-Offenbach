// struct fuer button (und remote?) inputs
// loop kann zum debuggen genutzt werden

const int pinA = 7;
const int pinB = 6;
const int pinC = 4;
const int pinD = 5;
unsigned long currentTime = 0;
unsigned long debounce_duration = 50;

struct modul_button {
  const int pin{};
  unsigned long lastPressed;

  // true entspricht einen Knopfdruck
  // should include pullup
  bool isPressed = false;
  bool wasPreseed = false;
  bool state = false;

  modul_button(int _pin)
    : pin(_pin) {}

  bool check() {
    isPressed = digitalRead(pin);
    return isPressed;
  }
  bool checkDebounce() {
    isPressed = check();

    if (isPressed == false) {
      wasPreseed = isPressed;
      return false;
    }  // Knopf gedrückt?

    if (isPressed == wasPreseed)
      return false;  // neuer tastendruck?

    if (currentTime - lastPressed > debounce_duration)  // debounce
    {
      wasPreseed = isPressed;
      lastPressed = currentTime;
      return true;
    }
  }
};

modul_button button[] = {
  modul_button(pinA),
  modul_button(pinB),
  modul_button(pinC),
  modul_button(pinD),
};

void setup() {
  for (modul_button &taste : button) {
    pinMode(taste.pin, INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  currentTime = millis();

  for (modul_button &taste : button) {
    if (taste.checkDebounce()) {
      Serial.print(taste.pin);
      Serial.println("> pin CheckDebounce sends True");
    }
  }
  for (modul_button &taste : button) {
    if (taste.check()) {
      Serial.print(taste.pin);
      Serial.println("> pin Check sends True");
    }
  }
}
