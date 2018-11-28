#include "volca_beats.h"

void setup() {
  //beat
  Serial.begin(31250);

  // bass
  Serial1.begin(31250);
}

void loop() {
  // put your main code here, to run repeatedly:
  playDrum(KICK);
  playBass(50);
}

void playDrum(int drum) {
  sendDrum(NOTE_ON, drum, 127);
  delay(100);
  sendDrum(NOTE_OFF, drum, 0);
  delay(100);
}

void sendDrum(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void playBass(int note) {
  sendBass(NOTE_ON, note, 127);
  delay(100);
  sendBass(NOTE_OFF, note, 0);
  delay(100);
}

void sendBass(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}
