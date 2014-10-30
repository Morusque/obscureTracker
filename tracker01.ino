
#include <avr/pgmspace.h>
#include <TVout.h>
#include <video_gen.h>
#include <EEPROM.h>
#include <Controllers.h>

#define W 136
#define H 98

#define NBFREQS 109
#define NBBEATS 16
#define EDITMODES 5
#define BEATYSIZE 4
#define NBCOMMANDS 14
#define NBPARAMS 14
#define NBSLOTS 8

void (*game)();
TVout tv;

byte x = 0;
byte y = 0;

byte notes[NBBEATS];
byte durations[NBBEATS];
byte commands[NBBEATS];
byte values[NBBEATS];

byte currentBeat = 0;
byte editRaw = 0;
byte editMode = 4;

int t=0;

int nbFrames = 16;
int swing = 3;
int frameMs = 5;
int currentFrame = 0;
long lastMillis=0;
int thisBeatMillis=0;

byte saveSlot=0;

int geShiftNot = 0;
int geShiftDur = 0;
int geShiftCom = 0;
int geShiftVal = 0;
boolean geAct = true;// TODO false ? mode ?

byte geFxSelect = 0;
boolean geFxAct = false;
byte geRtLength = 3;
byte geRtStart = 0;
int geRtAct = -1;

int geTrans = 0;

byte rndMode=5;

byte seqFxMode = 0;
boolean seqFxAct = false;
byte seqFxOctRange = 0;

int syncMode = 1;// 0=stop, 1=play, 2=sync, 3=tap

int visuPos=0;

byte copySel=0;
byte pasteSel=0;

PROGMEM const prog_uint16_t mToF[NBFREQS] = {
  31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,92,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,4435,4699,4978,5274,5588,5920,6272,6645,7040,7459,7902,8372,8870,9397,9956,10548,11175,11840,12544,13290,14080,14917,15804};

const prog_uint8_t symbols[] PROGMEM = {
#include "bitmaps.h"
};

void setup()  {
  tv.begin(_PAL, W, H);// or _NTCS
  randomSeed(analogRead(0));
  generateRandom(5);
}

void loop() {
  keyPressing();
  displaying();
  sounding();
  handleTiming();
}


