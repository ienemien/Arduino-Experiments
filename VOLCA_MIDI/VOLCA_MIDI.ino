#include "volca_beats.h"

//void setup() {
//  // Set MIDI baud rate:
//  Serial.begin(31250);
//}

//void loop() {
//  send(PARAM_CHANGE, HAT_GRAIN, 127);
//  send(PARAM_CHANGE, STUTTER_TIME, 5);
//  send(PARAM_CHANGE, STUTTER_DEPTH, 50);
//  send(PARAM_CHANGE, PL_KICK, 127);
//  play(SNARE);
//  play(KICK);
//  play(KICK);
//  play(KICK);
//  send(PARAM_CHANGE, PL_KICK, 10);
//  play(KICK);
//  play(KICK);
//  play(KICK);
//  play(KICK);
//  play(LO_TOM);
//  play(HI_TOM);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 127);
//  play(CL_HAT);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 110);
//  play(CL_HAT);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 100);
//  play(CL_HAT);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 90);
//  play(CL_HAT);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 20);
//  play(CL_HAT);
//  send(PARAM_CHANGE, DECAY_CL_HAT, 0);
//  send(PARAM_CHANGE, HAT_GRAIN, 10);
//  play(CL_HAT);
//  play(CL_HAT);
//  play(CL_HAT);
//  play(OP_HAT);
//  play(CLAP);
//  play(CLAVES);
//  play(AGOGO);
//  setPcmSpeed(PCM_CRASH, 127);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 100);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 80);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 60);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 40);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 20);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 10);
//  play(CRASH);
//  setPcmSpeed(PCM_CRASH, 2);
//  play(CRASH);
//}

void play(int drum) {
  send(NOTE_ON, drum, 127);
  delay(100);
  send(NOTE_OFF, drum, 0);
  delay(100);
}

//value from 0 to 127
void setPcmSpeed(int drum, int value) {
  send(PARAM_CHANGE, drum, value);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void send(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
