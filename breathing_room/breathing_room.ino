#include <MIDI.h>
#include <Ultrasonic.h>
#include "volca_bass.h"
#include "volca_beats.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

/*
   Pass as a parameter the trigger and echo pin, respectively,
   or only the signal pin (for sensors 3 pins), like:
   Ultrasonic ultrasonic(13);
*/
Ultrasonic ultrasonic(50, 51);

#define VIBRATION_PIN A0

int bpm = 60;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  volcaBeats.begin(MIDI_CHANNEL_OMNI);
  volcaBass.begin(MIDI_CHANNEL_OMNI);
  volcaBass.sendRealTime(midi::Start);
  volcaBeats.sendRealTime(midi::Start);
}

void loop() {

  volcaBass.sendControlChange(LFO_RATE, getRate(), 1);

  int pitch = getPitch();
  volcaBass.sendControlChange(VCO_PITCH_1, pitch, 1);
  volcaBass.sendControlChange(VCO_PITCH_2, pitch, 1);
  volcaBass.sendControlChange(VCO_PITCH_3, pitch, 1);

  // bass is synced with beats through the sync cable
  // beats controls the tempo
  quarterNotePassed();
}

int getRate() {
  int vibration = analogRead(VIBRATION_PIN);
  return map(vibration, 0, 1023, 20, 127);
}

int getPitch() {
  int distanceCm = ultrasonic.read();
  return map(distanceCm, 0, 127, 127, 0);
}

void quarterNotePassed() {
  unsigned int msPerMinute = (unsigned int)1000 * 60;
  unsigned int msPerBeat = msPerMinute / bpm;
  int pulseDelay = msPerBeat / 24;
  for (int i = 0; i < 24; i++) {
    volcaBeats.sendRealTime(midi::Clock);
    delay(pulseDelay);
  }
}
