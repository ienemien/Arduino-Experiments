// connect GND of UNO to GND of MEGA
// connect A4 (SDA pin) of UNO to SDA pin 20 of MEGA
// connect A5 of UNO to SCL pin 21 of MEGA

#include <Wire.h>

#define A_SHAKE A0

bool inPeak = false;
int bpm = 100;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);           // join i2c bus with address #8
  Wire.onRequest(sendBpm); // register event
  pinMode(A_SHAKE, INPUT);
}

void loop() {
  calculateBpm();
  Serial.println(bpm);
}

void sendBpm() {
  Serial.println("send bpm");
  // divide int over two bytes
  byte intArray[2];
  intArray[0] = (bpm >> 8) & 0xFF;
  intArray[1] = bpm & 0xFF;
  Wire.write(intArray, 2);
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
    int newBpm = beats * 4;
    bpm = newBpm > 50 ? newBpm : 50;
  }
