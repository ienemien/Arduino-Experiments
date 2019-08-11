#include <MIDI.h>
#include "volca_bass.h"
#include "volca_beats.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

void setup() {
   volcaBeats.begin(MIDI_CHANNEL_OMNI);
   volcaBass.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  //test to see if I can send two midi outputs at the same time
   volcaBeats.sendRealTime(midi::Start);
   delay(10000);
   volcaBass.sendRealTime(midi::Start);
   delay(10000);
   volcaBeats.sendRealTime(midi::Stop);
   delay(10000);
   volcaBass.sendRealTime(midi::Stop);
}
