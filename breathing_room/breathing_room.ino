#include <MIDI.h>
#include <Ultrasonic.h>
#include <DHT.h>
#include "volca_bass.h"
#include "volca_beats.h"


#define VIBRATION_PIN A0
#define DHT11_PIN A1 //temperature + humidity
#define DHTTYPE DHT11   // DHT 11

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, volcaBeats); // volca beats midi connector on TX0
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, volcaBass); // volca bass midi connector on TX1

/*
   Pass as a parameter the trigger and echo pin, respectively,
   or only the signal pin (for sensors 3 pins), like:
   Ultrasonic ultrasonic(13);
*/
Ultrasonic ultrasonic(50, 51);

DHT dht(DHT11_PIN, DHTTYPE);


int bpm = 60;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  dht.begin();
  setBpmFromTemperature();
  volcaBeats.begin(MIDI_CHANNEL_OMNI);
  volcaBass.begin(MIDI_CHANNEL_OMNI);
  volcaBass.sendRealTime(midi::Start);
  volcaBeats.sendRealTime(midi::Start);
}

void loop() {
  setBmpFromTemperature();
  volcaBass.sendControlChange(LFO_RATE, getRateFromVibration(), 1);

  volcaBass.sendControlChange(VCO_PITCH_1, getPitchFromDistance(), 1);
  volcaBass.sendControlChange(VCO_PITCH_2, getPitchFromDistance(), 1);
  volcaBass.sendControlChange(VCO_PITCH_3, getPitchFromDistance(), 1);

  // bass is synced with beats through the sync cable
  // beats controls the tempo
  quarterNotePassed();
}

int setBmpFromTemperature() {
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  bpm = map(temperature, 15, 30, 50, 160);
}

int getRateFromVibration() {
  int vibration = analogRead(VIBRATION_PIN);
  return map(vibration, 0, 1023, 20, 80);
}

int getPitchFromDistance() {
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
