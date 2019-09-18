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


int bpm = 30;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  dht.begin();
  volcaBeats.begin(MIDI_CHANNEL_OMNI);
  volcaBeats.sendRealTime(midi::Stop);
  volcaBass.begin(MIDI_CHANNEL_OMNI);
  volcaBass.sendRealTime(midi::Stop);
  //setBpmFromTemperature();
  //volcaBass.sendRealTime(midi::Start);
  //volcaBeats.sendRealTime(midi::Start);
}

void loop() {
  //setBpmFromTemperature();
  //volcaBass.sendControlChange(LFO_RATE, getRateFromVibration(), 1);

  volcaBass.sendControlChange(VCO_PITCH_1, getPitchFromDistance(), 1);
  //volcaBass.sendControlChange(VCO_PITCH_2, getPitchFromDistance(), 1);
  //volcaBass.sendControlChange(VCO_PITCH_3, getPitchFromDistance(), 1);

  //volcaBass.sendControlChange(EG_ATTACK, getAttackFromHumidity(), 1);
  int business = getBusiness();
  if (business < 300) {
    playIdle();
  } else if (business > 600) {
    playFast();
  } else {
    playMellow();
  }
}

void playIdle() {
  bpm = 30;
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  eighthNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  eighthNotePassed();
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(38, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOn(38, 80, 1);
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(41, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(41, 80, 1);
}

void playMellow() {
  bpm = 60;
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  eighthNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  eighthNotePassed();
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(38, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOn(38, 80, 1);
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(41, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(41, 80, 1);
}

void playFast() {
  bpm = 120;
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  eighthNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  eighthNotePassed();
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(43, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(43, 80, 1);
  volcaBeats.sendNoteOn(KICK, 80, 1);
  volcaBass.sendNoteOn(38, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOn(38, 80, 1);
  volcaBeats.sendNoteOn(SNARE, 80, 1);
  volcaBass.sendNoteOn(41, 80, 1);
  quarterNotePassed();
  volcaBass.sendNoteOff(41, 80, 1);
}

int setBpmFromTemperature() {
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  bpm = map(temperature, 15, 30, 50, 160);
}

int getAttackFromHumidity() {
  // Read temperature as Celsius (the default)
  float humidity = dht.readHumidity();
  return map(humidity, 30, 100, 0, 127);
}

int getRateFromVibration() {
  int vibration = analogRead(VIBRATION_PIN);
  int rate = 20;
  if (vibration > 30) {
    rate = map(vibration, 0, 1023, 20, 80);
  }
  return rate;
}

int getBusiness() {
  return analogRead(VIBRATION_PIN);
}

int getPitchFromDistance() {
  int distanceCm = ultrasonic.read();
  return map(distanceCm, 0, 127, 21, 80);
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

void eighthNotePassed() {
  unsigned int msPerMinute = (unsigned int)1000 * 60;
  unsigned int msPerBeat = msPerMinute / bpm;
  int pulseDelay = msPerBeat / 24;
  for (int i = 0; i < 12; i++) {
    volcaBeats.sendRealTime(midi::Clock);
    delay(pulseDelay);
  }
}
