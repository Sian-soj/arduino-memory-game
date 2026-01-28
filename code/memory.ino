#define NUM_LEDS 4 //Using four leds
#define MAX_LEVEL 20 //Number of Levels

int ledPins[NUM_LEDS] = {8, 9, 10, 11}; //Connect Led anode to Digital pins (8,9,10,11)
int buttonPins[NUM_LEDS] = {2, 3, 4, 5}; //Connect Buttons to Digital pins (2,3,4,5)

int sequence[MAX_LEVEL];
int level = 1;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(A0));
}

void loop() {
  generateSequence();
  showSequence();

  if (!getUserInput()) {
    gameOver();
    level = 1;
  } else {
    level++;
    delay(1000);
  }
}

void generateSequence() {
  sequence[level - 1] = random(0, NUM_LEDS);
}

void showSequence() {
  for (int i = 0; i < level; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);
    delay(500);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(300);
  }
}

bool getUserInput() {
  for (int i = 0; i < level; i++) {
    int pressed = waitForButton();
    if (pressed != sequence[i]) {
      return false;
    }
  }
  return true;
}

int waitForButton() {
  while (true) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
        digitalWrite(ledPins[i], LOW);
        while (digitalRead(buttonPins[i]) == LOW); // wait for release
        return i;
      }
    }
  }
}

void gameOver() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(300);
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(300);
  }
}
