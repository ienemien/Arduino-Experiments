#include "volca_beats.h"

#include <Ultrasonic.h>

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic(50, 51);

int pitch = 100;

void setup() {
  //beat
  Serial.begin(31250);

  // bass
  Serial1.begin(31250);

  //bpm in
  Serial3.begin(9600);
}

void loop() {
  int bpm = 60;
  /**  check if data has been sent from the computer: */
  while (Serial3.available()) {
    /* read the most recent byte */
    bpm = Serial3.read();
  }
  playRhytm(bpm);
}

void playRhytm(int bpm) {
  unsigned int ms_per_minute = (unsigned int)1000*60;
  unsigned int ms_per_beat = ms_per_minute/bpm;
  for(int i = 0; i < 8; i++) {
      //todo set delay according to bpm
      sendDrum(NOTE_ON, KICK, 127);
      sendDrum(NOTE_ON, CL_HAT, 127);
      getPitch();
      sendBass(NOTE_ON, pitch, 127);
      delay(ms_per_beat);
      sendDrum(NOTE_OFF, KICK, 0);
      sendDrum(NOTE_OFF, CL_HAT, 0);
      sendBass(NOTE_OFF, pitch, 0);

      sendDrum(NOTE_ON, CL_HAT, 127);
      getPitch();
      sendBass(NOTE_ON, pitch, 127);
      delay(ms_per_beat);
      sendDrum(NOTE_OFF, CL_HAT, 127);
      sendBass(NOTE_OFF, pitch, 0);
      
      sendDrum(NOTE_ON, CL_HAT, 127);
      sendDrum(NOTE_ON, SNARE, 127);
      getPitch();
      sendBass(NOTE_ON, pitch, 127);
      delay(ms_per_beat);
      sendDrum(NOTE_OFF, CL_HAT, 0);
      sendDrum(NOTE_OFF, SNARE, 127);
      sendBass(NOTE_OFF, pitch, 0);
    
      sendDrum(NOTE_ON, CL_HAT, 127);
      getPitch();
      sendBass(NOTE_ON, pitch, 127);
      delay(ms_per_beat);
      sendDrum(NOTE_OFF, CL_HAT, 127);
      sendBass(NOTE_OFF, pitch, 0);
    }
}

void getPitch() {
  int distanceCm = ultrasonic.read();
  pitch = map(distanceCm, 0, 127, 100, 20 );
  }

void sendDrum(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void sendBass(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
}
