  // struct fuer button (und remote?) inputs
// loop kann zum debuggen genutzt werden
// ToDo
//  beispiele zum initialierseren und for each schleifen
// nutzten von return values

const int pinA = 13;
const int pinB = 11;
const int pinC = 10;
const int pinD = 12;
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
    pinMode(taste.pin, INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop() {
  currentTime = millis();

  int idx = 0;
  for (modul_button &taste : button) {
    if (taste.checkDebounce()) {
      Serial.print(taste.pin);
      Serial.println("> idx | CheckDebounce sends True");
    }
  }
  idx = 0;
  for (modul_button &taste : button) {
    if (taste.check()) {
      Serial.print(taste.pin);
      Serial.println("> idx | Check sends True");
    }
  }
}
