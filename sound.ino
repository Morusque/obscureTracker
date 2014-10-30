
float prevFrequency=0;
byte prevCommand=0;
byte prevValue=0;
void sounding() {
  boolean volume = true;
  int thisCurrentBeat=currentBeat;
  if (seqFxAct && seqFxMode==3) {
    thisCurrentBeat=NBBEATS-currentBeat;
  }
  if (geRtAct>-1)  {
    thisCurrentBeat = geRtStart + geRtAct;
  }
  else {
    geRtStart=currentBeat;
  }
  byte thisDuration = durations[(thisCurrentBeat+geShiftDur+NBBEATS)%NBBEATS];
  if (seqFxAct && seqFxMode==2) {
    byte maxDuration=0;
    for (int i=0;i<NBBEATS;i++) {
      maxDuration=max(maxDuration,durations[i]);
    }
    thisDuration=maxDuration-thisDuration;
  }
  if (currentFrame>=thisDuration) volume = false;
  if (seqFxAct && seqFxMode==0) {
    volume = true;
  }
  int noteIndex = notes[(thisCurrentBeat+geShiftNot+NBBEATS)%NBBEATS];
  if (geAct) {
    noteIndex = constrain(noteIndex+(geTrans),0,NBFREQS);
    while (noteIndex>=NBFREQS) noteIndex-=12;
    while (noteIndex<0)        noteIndex+=12;
  }
  if (seqFxAct && seqFxMode==1) {
    while (noteIndex<seqFxOctRange-7) noteIndex+=12;
    while (noteIndex>seqFxOctRange+7) noteIndex-=12;
  }
  while (noteIndex<0||noteIndex>=NBFREQS) noteIndex = (noteIndex+NBFREQS)%NBFREQS;
  float thisFrequency = pgm_read_word_near(mToF+noteIndex);
  byte thisCommand = commands[(thisCurrentBeat+geShiftCom+NBBEATS)%NBBEATS];
  if (geFxAct) {
    thisCommand=geFxSelect;
  }  
  byte thisValue = values[(thisCurrentBeat+geShiftVal+NBBEATS)%NBBEATS];
  if (thisCommand==12) {// repeat
    thisCommand = prevCommand;
    if (currentFrame==0) thisValue = (byte)floor((random(thisValue) + prevValue)%128);
  }
  if (thisCommand==13) {// random
    if (currentFrame==0) thisCommand = (byte)random(11);
    else thisCommand=prevCommand;
  }
  if (thisCommand==1) {// pitch to
    thisFrequency += ((thisValue-64)*100)/currentFrame;
  }
  if (thisCommand==2) {// tune
    thisFrequency = thisFrequency * (1 + (((float)thisValue-64)/(64*12)));
  }
  if (thisCommand==3) {// octaver
    thisFrequency = thisFrequency * pow(2,currentFrame*16/(128-thisValue));
  }  
  if (thisCommand==4) {// legato
    thisFrequency = (thisFrequency*((float)127-thisValue)/127) + (prevFrequency*(float)thisValue/127);
  }
  if (thisCommand==5) {// chord
    if ((int)floor(currentFrame/3)%3==1) {
      noteIndex = (notes[(thisCurrentBeat+geShiftNot+NBBEATS)%NBBEATS]+((thisValue>>0)&0b00001111)+NBFREQS)%NBFREQS;
      thisFrequency = pgm_read_word_near(mToF+noteIndex);
    }
    if ((int)floor(currentFrame/3)%3==2) {
      noteIndex = (notes[(thisCurrentBeat+geShiftNot+NBBEATS)%NBBEATS]+((thisValue>>4)&0b00001111)+NBFREQS)%NBFREQS;
      thisFrequency = pgm_read_word_near(mToF+noteIndex);       
    }    
  }
  if (thisCommand==6) {// vibrato
    thisFrequency += sin(currentFrame/2.5)*thisValue;
  }
  if (thisCommand==7) {// trill
    if (currentFrame==thisValue%10) thisFrequency += floor(1+thisValue/10)*50;
  }
  if (thisCommand==8) {// tremolo
    volume = volume & ((int)floor(currentFrame/(thisValue+1))%2==0);
  }
  if (thisCommand==9) {// noise
    thisFrequency += random(-thisValue*5,thisValue*5);
  }
  if (thisCommand==10) {// delay
    volume = volume & (currentFrame>=thisValue);
  }  
  if (thisCommand==11) {// goto
    currentBeat = (byte)thisValue%NBBEATS;
  }
  if (thisCommand!=0) prevCommand = thisCommand;
  thisFrequency = constrain(thisFrequency,20,22000);
  prevFrequency = thisFrequency;
  prevValue = thisValue;
  if (syncMode!=1) volume=false;
  if (volume) tv.tone(floor(thisFrequency));
  else tv.noTone();
}



