#include <MIDI.h>
#include <Ultrasonic.h>

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic(8, 7);

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop()
{
  int distanceCm = ultrasonic.distanceRead();
  int note = map(distanceCm, 0, 127, 100, 20 );
  MIDI.sendNoteOn(note, 127, 1);
  delay(100);		       
  MIDI.sendNoteOff(note, 0, 1);
  delay(100);
}
