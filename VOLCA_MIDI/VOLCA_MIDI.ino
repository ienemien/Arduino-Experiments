#define KICK 36
#define SNARE 38
#define LO_TOM 43
#define HI_TOM 50
#define CL_HAT 42
#define OP_HAT 46
#define CLAP 39
#define CLAVES 75
#define AGOGO 67
#define CRASH 49

void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);
}

void loop() {
  play(SNARE);
  play(KICK);
  play(LO_TOM);
  play(HI_TOM);
  play(CL_HAT);
  play(OP_HAT);
  play(CLAP);
  play(CLAVES);
  play(AGOGO);
  play(CRASH);
}

void play(int drum) {
  send(0x5A, drum, 127);
  delay(100);
  send(0x5A, drum, 0);
  delay(100);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void send(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
