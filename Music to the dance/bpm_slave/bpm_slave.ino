#include <Wire.h>

#define A_SHAKE A0

bool inPeak = false;
int bpm = 100;

void setup() {
  Wire.begin(8);           // join i2c bus with address #8
  Wire.onRequest(sendBpm); // register event
  Serial.begin(9600);
  pinMode(A_SHAKE, INPUT);
}

void loop() {
  calculateBpm();
}

void sendBpm() {
  Wire.write(bpm);
  Serial.println("bpm requested");
}

void calculateBpm() 
{
  int beats = 0;
  
    //run for 15 seconds and measure beats
    for(int i = 0; i <= 150; i++)
    {
      int analogShake = analogRead(A_SHAKE);
  
      if(analogShake > 200)
      {
        if(!inPeak) {
            beats++;
            inPeak = true;
        }
      } else {
        inPeak = false;
      }
      delay(100);
    }
    bpm = beats * 4;
    Serial.println(bpm);
  }
