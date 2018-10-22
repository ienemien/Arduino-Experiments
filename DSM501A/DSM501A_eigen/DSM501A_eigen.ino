#include<string.h>

#define RED 11
#define ORANGE 12
#define GREEN 13

byte buff[2];
int pin = 8;//DSM501A input D8
unsigned long duration_ms;
unsigned long starttime_ms;
unsigned long endtime_ms;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

int i = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  starttime_ms = millis();
}

void loop()
{
  duration_ms = pulseIn(pin, LOW);
  Serial.print("duration_ms:");
  Serial.print(duration_ms);
  Serial.print("\n");
  lowpulseoccupancy += duration_ms;//opgetelde tijd van lage puls in seconden
  endtime_ms = millis();
  if ((endtime_ms - starttime_ms) > sampletime_ms)
  {
    digitalWrite(GREEN, LOW);
    digitalWrite(ORANGE, LOW);
    digitalWrite(RED, LOW);
    ratio = (lowpulseoccupancy - endtime_ms + starttime_ms + sampletime_ms) / (sampletime_ms * 10.0); // Integer percentage 0=>100
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
    Serial.print("lowpulseoccupancy:");
    Serial.print(lowpulseoccupancy);
    Serial.print("\n");
    Serial.print("ratio:");
    Serial.print(ratio);
    Serial.print("\n");
    Serial.print("DSM501A concentration:");
    Serial.println(concentration);
    Serial.print("\n\n");

    if (ratio < 5)
    {
      digitalWrite(GREEN, HIGH);
    } else if (ratio >= 10)
    {
      digitalWrite(RED, HIGH);
    } else
    {
      digitalWrite(ORANGE, HIGH);
    }

    lowpulseoccupancy = 0;
    starttime_ms = millis();
  }

}

