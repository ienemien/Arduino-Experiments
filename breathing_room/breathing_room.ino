#include <MIDI.h>
#include "volca_bass.h"
#include "volca_beats.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

#define VIBRATION_PIN A0

int bpm = 120;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  volcaBeats.begin(MIDI_CHANNEL_OMNI);
  volcaBass.begin(MIDI_CHANNEL_OMNI);
  volcaBass.sendRealTime(midi::Start);
  volcaBeats.sendRealTime(midi::Start);
}

void loop() {

  // bass is synced with beats through the sync cable
  // beats controls the tempo
  int vibration = analogRead(VIBRATION_PIN);
  if (vibration > 30) {
    bpm = map(vibration, 30, 1020, 60, 200);
  }

  unsigned int msPerMinute = (unsigned int)1000 * 60;
  unsigned int msPerBeat = msPerMinute / bpm;

  playBar(msPerBeat);
}

void playBar(int msPerBeat) {
  for (int i = 0; i < 4; i++) {
    delay(msPerBeat);
    quarterNotePassed();
  }
}

void quarterNotePassed() {
  for (int i = 0; i < 24; i++) {
    volcaBeats.sendRealTime(midi::Clock);
  }
}
