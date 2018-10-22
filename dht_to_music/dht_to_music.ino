// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 10     // pin for DHT sensor
#define PIEZO_PIN 8   //pin for piezo
#define DHTTYPE DHT11   // DHT 11

#define WHOLE_NOTE   1000
#define HALF_NOTE 1000/2
#define QUARTER_NOTE  1000/4
#define EIGHTH_NOTE 1000/8

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  //delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print(" \n");
  Serial.print("Temperature: ");
  Serial.print(temperature); 
  Serial.print(" *C ");
  Serial.print("\n");

  //convert temperature to pitch
  long pitch = map(temperature, 0, 30, 3000, 30);
  Serial.print("pitch = ");
  Serial.print(pitch);
  Serial.print("\n");

  //convert humidity to duration
  long duration = map(humidity, 30, 100, 100, 1000);
  Serial.print("duration = ");
  Serial.print(duration);
  Serial.print("\n");
  
  playMelody(pitch, duration);
}

void playMelody(long pitch, long duration) {
  tone(PIEZO_PIN, pitch, duration);
  delay(duration * 1.30);
  tone(PIEZO_PIN, pitch-20, duration);
  delay(duration * 1.30);
  tone(PIEZO_PIN, pitch + 10, duration);
  delay(duration * 1.30);
}
