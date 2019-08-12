#include <MIDI.h>
#include "volca_bass.h"
#include "volca_beats.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

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
  int vibration = analogRead(VIBRATION_PIN);
  int pitch1 = map(vibration, 0, 1023, 0, 255);
  //volcaBass.sendControlChange(VCO_PITCH_1, pitch1, 1);
  //volcaBass.sendControlChange(VCO_PITCH_2, pitch1, 1);
  //volcaBass.sendControlChange(VCO_PITCH_3, pitch1, 1);
  volcaBass.sendControlChange(LFO_RATE, pitch1, 1);

  // bass is synced with beats through the sync cable
  // beats controls the tempo
  quarterNotePassed();
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
