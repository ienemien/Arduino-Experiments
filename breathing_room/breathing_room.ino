#include <MIDI.h>
#include "volca_bass.h"
#include "volca_beats.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

void setup() {
  volcaBeats.begin(MIDI_CHANNEL_OMNI);
  volcaBass.begin(MIDI_CHANNEL_OMNI);
  volcaBass.sendRealTime(midi::Start);
}

void loop() {
  // bass is synced with beats through the sync cable
  // beats controls the tempo
  volcaBeats.sendNoteOn(KICK, 100, 1);
  delay(500);
  volcaBeats.sendNoteOn(KICK, 100, 1);
  quarterNotePassed();
  delay(500);
  volcaBeats.sendNoteOn(KICK, 100, 1);
  quarterNotePassed();
  delay(500);
  volcaBeats.sendNoteOn(KICK, 100, 1);
  quarterNotePassed();
  delay(500);
  volcaBeats.sendNoteOn(KICK, 100, 1);
  quarterNotePassed();
}

void wholeNotePassed() {
  for (int i = 0; i < 4; i++) {
    quarterNotePassed();
  }
}

void quarterNotePassed() {
  for (int i = 0; i < 24; i++) {
    volcaBeats.sendRealTime(midi::Clock);
  }
}
