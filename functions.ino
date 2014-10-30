
void handleTiming() {
  byte thisNbFrames = nbFrames;
  if (currentBeat%2==0) thisNbFrames += swing;
  else thisNbFrames -= swing;
  while (millis()-lastMillis < frameMs) {
    delayMicroseconds(100);
  }
  lastMillis = millis();
  currentFrame++;
  if (currentFrame>=thisNbFrames) {
    if (syncMode==1) {
      if (!seqFxAct || seqFxMode!=0) {
        currentFrame=0;
        currentBeat=(currentBeat+1)%NBBEATS;
      }
      else{
        currentFrame=min(currentFrame,127);
      }
      if (geRtAct!=-1) geRtAct=(geRtAct+1)%geRtLength;
    } 
    else {
      currentFrame=0;
    }
  }
}

void generateRandom(byte rndMode) {
  if (rndMode==4||rndMode==5) {
    nbFrames = floor(random(15)+15);
    swing = floor(random(nbFrames/2));
    frameMs = floor(random(3)+4);
  }
  byte maxNote = floor(random(NBFREQS));  
  for (int i=0;i<NBBEATS;i++) {
    if (rndMode==0||rndMode==5) notes[i] = floor(random(maxNote));
    if (rndMode==1||rndMode==5) durations[i] = floor(random(nbFrames));
    if (rndMode==2||rndMode==5) {
      if (random(100)<50) commands[i] = floor(random(11));
      else commands[i] = 0;
    }
    if (rndMode==3||rndMode==5) values[i] = floor(random(128));
  }
}

void saveSong() {
  int address=saveSlot*(4*NBBEATS+3);
  EEPROM.write(address+0,(byte)nbFrames);
  EEPROM.write(address+1,(byte)swing);
  EEPROM.write(address+2,(byte)frameMs);
  address+=3;
  for(byte i=0;i<NBBEATS;i++) {
    EEPROM.write(address+i*4+0,notes[i]);
    EEPROM.write(address+i*4+1,durations[i]);
    EEPROM.write(address+i*4+2,commands[i]);
    EEPROM.write(address+i*4+3,values[i]);
  }
  address+=4*NBBEATS;
}

void loadSong() {
  int address=saveSlot*(4*NBBEATS+3);
  nbFrames=EEPROM.read(address+0);
  swing=EEPROM.read(address+1);
  frameMs=EEPROM.read(address+2);
  address+=3;
  for(byte i=0;i<NBBEATS;i++) {
    notes[i]=EEPROM.read(address+i*4+0);
    durations[i]=EEPROM.read(address+i*4+1);
    commands[i]=EEPROM.read(address+i*4+2);
    values[i]=EEPROM.read(address+i*4+3);
  }
  address+=4*NBBEATS;
}

void dumpMemory() {
  /*
  Serial.begin(9600);
  for (int i=0;i<1024;i++) Serial.println(EEPROM.read(i));
  Serial.end();
  */
}


