
#define A_SHAKE A0
#define D_SHAKE 12

bool inPeak = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A_SHAKE, INPUT);
  pinMode(D_SHAKE, INPUT);
}

void loop() {
  int bpm = calculateBpm();
  Serial.print("\n");
  Serial.print("========================");
  Serial.print("BPM IS ");
  Serial.print(bpm);
  Serial.print("\n");
  Serial.print("========================");
  delay(5000);
}

bool isBeat(int value) 
{
  if(value > 500) 
  {
    return true;
  }
  return false;
}

int calculateBpm() 
{
  int beats = 0;
  
    //run for 15 seconds and measure beats
    for(int i = 0; i <= 150;i++)
    {
      int analogShake = analogRead(A_SHAKE);
  
      if(isBeat(analogShake))
      {
        if(!inPeak) {
            Serial.print("IS BEAT: ");
            Serial.print(analogShake);
            Serial.print("\n");
            inPeak = true;
            beats++;
          }
      } else {
        inPeak = false;
        Serial.print("no beat: ");
        Serial.print(analogShake);
        Serial.print("\n");
      }
      delay(100);
    }
    return beats * 4;
  }
