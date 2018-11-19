#include "volca_beats.h"

#define A_SHAKE A0
bool inPeak = false;
unsigned int bpm = 0;

void setup() {
  inPeak = false;
  // Set MIDI baud rate:
  Serial.begin(31250);
  pinMode(A_SHAKE, INPUT);

  delay(10000);
  send(NOTE_ON, CLAVES, 127);
  send(NOTE_OFF, CLAVES, 0);
  bpm = calculateBpm();
}

void loop() {
  playRhytm(bpm);
}

void playRhytm(int bpm) {
  unsigned int ms_per_minute = (unsigned int)1000*60;
  unsigned int ms_per_beat = ms_per_minute/bpm;
  for(int i = 0; i < 8; i++) {
      //todo set delay according to bpm
      send(NOTE_ON, KICK, 127);
      send(NOTE_ON, CL_HAT, 127);
      delay(ms_per_beat);
      send(NOTE_OFF, KICK, 0);
      send(NOTE_OFF, CL_HAT, 127);
      
      send(NOTE_ON, CL_HAT, 127);
      delay(ms_per_beat);
      send(NOTE_OFF, CL_HAT, 127);
      
      send(NOTE_ON, CL_HAT, 127);
      send(NOTE_ON, SNARE, 127);
      delay(ms_per_beat);
      send(NOTE_OFF, CL_HAT, 0);
      send(NOTE_OFF, SNARE, 127);
    
      send(NOTE_ON, CL_HAT, 127);
      delay(ms_per_beat);
      send(NOTE_OFF, CL_HAT, 127);
    }
}

int calculateBpm() 
{
  int beats = 0;
  
    //run for 15 seconds and measure beats
    for(int i = 0; i <= 150; i++)
    {
      int analogShake = analogRead(A_SHAKE);
  
      if(analogShake > 200)
      {
        if(!inPeak) {
            beats++;
            inPeak = true;
        }
      } else {
        inPeak = false;
      }
      delay(100);
    }
    return beats * 4;
  }
