//note numbers
#define KICK 0x24
#define SNARE 0x26
#define LO_TOM 0x2B
#define HI_TOM 0x32
#define CL_HAT 0x2A
#define OP_HAT 0x2E
#define CLAP 0x27
#define CLAVES 0x4B
#define AGOGO 0x43
#define CRASH 0x31

//commands
#define NOTE_ON 0x90
#define NOTE_OFF 0x80
#define OTHER 0xB0

//part level data
#define PL_KICK 0x28
#define PL_SNARE 0x29
#define PL_LO_TOM 0x2A
#define PL_HI_TOM 0x2B
#define PL_CL_HAT 0x2C
#define PL_OP_HAT 0x2D
#define PL_CLAP 0x2E
#define PL_CLAVES 0x2F
#define PL_AGOGO 0x30
#define PL_CRASH 0x31

//pcm speed data
#define PCM_CLAP 0x32
#define PCM_CLAVES 0x33
#define PCM_AGOGO 0x34
#define PCM_CRASH 0x35

//stutter data
#define STUTTER_TIME 0x36
#define STUTTER_DEPTH 0x37

//decay data
#define DECAY_TOM 0x38
#define DECAY_CL_HAT 0x39
#define DECAY_OP_HAT 0x3A
#define HAT_GRAIN 0x3B

void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);
}

void loop() {
  send(OTHER, HAT_GRAIN, 127);
  send(OTHER, STUTTER_TIME, 5);
  send(OTHER, STUTTER_DEPTH, 50);
  send(OTHER, PL_KICK, 127);
  play(SNARE);
  play(KICK);
  play(KICK);
  play(KICK);
  send(OTHER, PL_KICK, 10);
  play(KICK);
  play(KICK);
  play(KICK);
  play(KICK);
  play(LO_TOM);
  play(HI_TOM);
  send(OTHER, DECAY_CL_HAT, 127);
  play(CL_HAT);
  send(OTHER, DECAY_CL_HAT, 110);
  play(CL_HAT);
  send(OTHER, DECAY_CL_HAT, 100);
  play(CL_HAT);
  send(OTHER, DECAY_CL_HAT, 90);
  play(CL_HAT);
  send(OTHER, DECAY_CL_HAT, 20);
  play(CL_HAT);
  send(OTHER, DECAY_CL_HAT, 0);
  send(OTHER, HAT_GRAIN, 10);
  play(CL_HAT);
  play(CL_HAT);
  play(CL_HAT);
  play(OP_HAT);
  play(CLAP);
  play(CLAVES);
  play(AGOGO);
  setPcmSpeed(PCM_CRASH, 127);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 100);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 80);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 60);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 40);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 20);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 10);
  play(CRASH);
  setPcmSpeed(PCM_CRASH, 2);
  play(CRASH);
}

void play(int drum) {
  send(NOTE_ON, drum, 127);
  delay(100);
  send(NOTE_OFF, drum, 0);
  delay(100);
}

//value from 0 to 127
void setPcmSpeed(int drum, int value) {
  send(OTHER, drum, value);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void send(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
