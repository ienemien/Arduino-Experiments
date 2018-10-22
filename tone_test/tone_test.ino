#include "pitches.h"
#include "durations.h"

#define PIEZO_PIN 8

void setup() {

}

void loop() {
  tone(PIEZO_PIN, NOTE_GS7, WHOLE_NOTE);
  delay(WHOLE_NOTE * 1.30);
  tone(PIEZO_PIN, NOTE_D4, HALF_NOTE);
  delay(HALF_NOTE * 1.30);
  tone(PIEZO_PIN, NOTE_E1, QUARTER_NOTE);
  delay(QUARTER_NOTE * 1.30);
}
