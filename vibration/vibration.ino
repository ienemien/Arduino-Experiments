
#define A_SHAKE A0

bool inPeak = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A_SHAKE, INPUT);
}

void loop() {
  int bpm = calculateBpm();
  //Serial.println(bpm);
  inPeak = false;
}

int calculateBpm() 
{
  int beats = 0;
  
    //run for 15 seconds and measure beats
    for(int i = 0; i <= 100; i++)
    {
      int analogShake = analogRead(A_SHAKE);
      Serial.println(analogShake);
  
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
    return beats * 6;
  }
