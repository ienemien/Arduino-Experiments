#include <MIDI.h>
#include "volca_bass.h"

 // Created and binds the MIDI interface to the default hardware Serial port
 MIDI_CREATE_DEFAULT_INSTANCE();

 void setup()
 {
     MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
 }

 void loop()
 {
     MIDI.sendRealTime(midi::Start);
     //MIDI.sendControlChange(OCTAVE, 0, 1);
     //MIDI.sendControlChange(VCO_PITCH_1, 10, 1);
     //MIDI.sendControlChange(SLIDE_TIME, 0, 1);
     //MIDI.sendControlChange(EG_ATTACK, 0, 1);
     //MIDI.sendControlChange(GATE_TIME, 0, 1);
     //MIDI.sendControlChange(LFO_RATE, 30, 1);
     //MIDI.sendPitchBend(80, 1);
     MIDI.sendControlChange(EXPRESSION, 4, 1);
     delay(3000);
     MIDI.sendRealTime(midi::Clock);
     //MIDI.sendControlChange(OCTAVE, 60, 1);
     //MIDI.sendControlChange(VCO_PITCH_1, 80, 1);
     //MIDI.sendControlChange(SLIDE_TIME, 66, 1);
    // MIDI.sendControlChange(EG_ATTACK, 127, 1);
     //MIDI.sendControlChange(LFO_RATE, 80, 1);
     //MIDI.sendControlChange(LFO_INT, 120, 1);
     MIDI.sendControlChange(EXPRESSION, 50, 1);
     delay(3000);
     MIDI.sendRealTime(midi::Clock);
     //MIDI.sendControlChange(OCTAVE, 127, 1);
     //MIDI.sendControlChange(VCO_PITCH_1, 120, 1);
     //MIDI.sendControlChange(SLIDE_TIME, 127, 1);
     //MIDI.sendControlChange(GATE_TIME, 90, 1);
     //MIDI.sendControlChange(LFO_RATE, 100, 1);
     MIDI.sendControlChange(EXPRESSION, 111, 1);
     delay(5000);
     MIDI.sendRealTime(midi::Stop);
     delay(3000);
 }
