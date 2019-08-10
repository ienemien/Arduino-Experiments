
//commands
#define NOTE_ON 0x90
#define NOTE_OFF 0x80
#define PARAM_CHANGE 0xB0

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
