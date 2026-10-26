/*
  Heart blood-flow model - 9 dual-colour (red/blue) LEDs
  Blue = deoxygenated (impure) blood, Red = oxygenated (pure) blood.

  Each LED is a 3-pin common-cathode red/blue LED.
  Blue leg -> 220 ohm -> Arduino pin, Red leg -> 330 ohm -> Arduino pin, common leg -> GND.

  Journey (one station lights at a time):
   1 Vena cavae  2 Right atrium  3 Right ventricle  4 Pulmonary artery
   5 Lungs (blue -> red)  6 Left atrium  7 Left ventricle  8 Aorta  9 Body (red -> blue)
*/
const uint8_t BLUE_PIN[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const uint8_t RED_PIN[9]  = {11, 12, 13, A0, A1, A2, A3, A4, A5};

// 'B' = blue, 'R' = red. First half of the step, then second half.
const char FIRST[9]  = {'B','B','B','B','B','R','R','R','R'};
const char SECOND[9] = {'B','B','B','B','R','R','R','R','B'};

const unsigned long STEP_MS = 900;   // time each station stays lit (make bigger = slower)

void allOff() {
  for (uint8_t i = 0; i < 9; i++) {
    digitalWrite(BLUE_PIN[i], LOW);
    digitalWrite(RED_PIN[i], LOW);
  }
}

void show(uint8_t i, char colour) {
  allOff();
  if (colour == 'B') digitalWrite(BLUE_PIN[i], HIGH);
  else               digitalWrite(RED_PIN[i], HIGH);
}

void setup() {
  for (uint8_t i = 0; i < 9; i++) {
    pinMode(BLUE_PIN[i], OUTPUT);
    pinMode(RED_PIN[i], OUTPUT);
  }
  allOff();
}

void loop() {
  for (uint8_t i = 0; i < 9; i++) {
    show(i, FIRST[i]);
    delay(STEP_MS / 2);
    show(i, SECOND[i]);
    delay(STEP_MS / 2);
  }
}
