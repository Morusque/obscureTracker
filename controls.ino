
int keyPressedTime = 0;
int retriggerTime = 40;
void keyPressing() {
  byte nbKeyPressed = 0;
  if(Controller.upPressed()&&Controller.downPressed()&&Controller.firePressed()) {
    if (editMode==0) {
      geShiftNot=0;
      geShiftDur=0;
      geShiftCom=0;
      geShiftVal=0;
      geFxAct=false;
      geRtAct=-1;
      geTrans=0;
      seqFxAct=false;
    }
    if (editMode==1) {
      if (keyPressedTime%retriggerTime==0) {
        byte highestNote = 0;
        for (int i=0;i<NBBEATS;i++) highestNote = max(highestNote,notes[i]);
        for (int i=0;i<NBBEATS;i++) if (notes[i]==highestNote && notes[i]>=12) notes[i]=notes[i]-12;
      }
    }
    if (editMode==2) {
      for (int  i=0;i<NBBEATS;i++) {
        durations[i]=min(durations[i],nbFrames-(swing*((i%2)*2-1)));
      }
    }
  }
  if(Controller.upPressed()) {
    if (keyPressedTime%retriggerTime==0) {
      if (Controller.firePressed()) editMode = (editMode-1+EDITMODES)%EDITMODES;
      else editRaw=(editRaw+(NBBEATS-1))%NBBEATS;
    }
    nbKeyPressed++;
  }
  if(Controller.downPressed()) {
    if (keyPressedTime%retriggerTime==0) {
      if (Controller.firePressed()) editMode = (editMode+1)%EDITMODES;
      else editRaw=(editRaw+1)%NBBEATS;
    }
    nbKeyPressed++;
  }
  if(Controller.rightPressed()) {
    if (keyPressedTime%retriggerTime==0) {
      if (editMode==0) {
        if (editRaw==0) {
          if (Controller.firePressed()) saveSong();
          else saveSlot=min(saveSlot+1,NBSLOTS-1);
        }
        if (editRaw==1) {
          syncMode=constrain(syncMode+1,0,3);
        }
        if (editRaw==2) {
          if (Controller.firePressed()) swing++;
          else nbFrames++;
          nbFrames=constrain(nbFrames,0,32);
          swing=constrain(swing,0,nbFrames);
        }
        if (editRaw==3) {
          if (Controller.firePressed()) {
            nbFrames=constrain(round(nbFrames/2),0,32);
            swing=constrain(round(swing/2),0,nbFrames);            
            frameMs=constrain(round(frameMs*2),0,100);
          }
          else frameMs=constrain(frameMs+1,0,100);
        }
        if (editRaw==4) {
          if (Controller.firePressed()) {
            byte newValues[NBBEATS];
            for (int i=0;i<NBBEATS;i++) newValues[i]=notes[(i+geShiftNot+NBBEATS)%NBBEATS];
            for (int i=0;i<NBBEATS;i++) notes[i]=newValues[i];
            geShiftNot=0;
          } 
          else {
            geShiftNot=constrain(geShiftNot-1,-NBBEATS,NBBEATS);
          }
        }
        if (editRaw==5) {
          if (Controller.firePressed()) {
            byte newValues[NBBEATS];
            for (int i=0;i<NBBEATS;i++) newValues[i]=durations[(i+geShiftDur+NBBEATS)%NBBEATS];
            for (int i=0;i<NBBEATS;i++) durations[i]=newValues[i];
            geShiftDur=0;
          } 
          else {
            geShiftDur=constrain(geShiftDur-1,-NBBEATS,NBBEATS);
          }
        }              
        if (editRaw==6) {
          if (Controller.firePressed()) {
            byte newValues[NBBEATS];
            for (int i=0;i<NBBEATS;i++) newValues[i]=commands[(i+geShiftCom+NBBEATS)%NBBEATS];
            for (int i=0;i<NBBEATS;i++) commands[i]=newValues[i];
            geShiftCom=0;
          } 
          else {
            geShiftCom=constrain(geShiftCom-1,-NBBEATS,NBBEATS);
          }
        }              
        if (editRaw==7) {
          if (Controller.firePressed()) {
            byte newValues[NBBEATS];
            for (int i=0;i<NBBEATS;i++) newValues[i]=values[(i+geShiftVal+NBBEATS)%NBBEATS];
            for (int i=0;i<NBBEATS;i++) values[i]=newValues[i];
            geShiftVal=0;
          } 
          else {
            geShiftVal=constrain(geShiftVal-1,-NBBEATS,NBBEATS);
          }
        }
        if (editRaw==8) {
          if (Controller.firePressed()) geFxAct=true;
          else geFxSelect=(geFxSelect+1)%NBCOMMANDS;
        }
        if (editRaw==9) {
          if (Controller.firePressed()) geRtAct=0;
          else geRtLength=min(geRtLength+1,NBBEATS-1);
        }
        if (editRaw==10) {
          if (Controller.firePressed()) {
            seqFxAct=true;
            if (seqFxMode==1) seqFxOctRange=notes[currentBeat];
          }
          else seqFxMode=min(seqFxMode+1,3);
        }        
        if (editRaw==11) {
          if (Controller.firePressed()) generateRandom(rndMode);
          else rndMode=min(rndMode+1,5);
        }
        if (editRaw==12) {
          if (Controller.firePressed()) geTrans=constrain(geTrans+12,-48,48);
          else geTrans=constrain(geTrans+1,-48,48);
        }
        if (editRaw==13) {
          if (Controller.firePressed()) {
            notes[pasteSel]=notes[copySel];
            durations[pasteSel]=durations[copySel];
            commands[pasteSel]=commands[copySel];
            values[pasteSel]=values[copySel];
          }
          else pasteSel=min(pasteSel+1,NBBEATS-1);
        }        
      }
      if (editMode==1) {
        int shiftBy = (1+(11*Controller.firePressed()));  
        if (Controller.downPressed()) {
          for (int i=0;i<NBBEATS;i++) {
            if (notes[i]+shiftBy<NBFREQS) notes[i]+=shiftBy;
            else while(notes[i]-shiftBy>=0) notes[i]-=shiftBy;
          }
        }
        else {
          if (notes[editRaw]+shiftBy<NBFREQS) notes[editRaw]+=shiftBy;
          else while(notes[editRaw]-shiftBy>=0) notes[editRaw]-=shiftBy;
        }
      }
      if (editMode==2) {
        if (Controller.firePressed()) durations[editRaw]=nbFrames-(swing*((editRaw%2)*2-1));
        else durations[editRaw]=(durations[editRaw]+1)%128;
      }
      if (editMode==3 &&  Controller.firePressed()) commands[editRaw]=(commands[editRaw]+1)%NBCOMMANDS;
      if (editMode==3 && !Controller.firePressed()) values[editRaw]=(values[editRaw]+1)%128;
    }
    nbKeyPressed++;
  }
  if(Controller.leftPressed()) {
    if (keyPressedTime%retriggerTime==0) {
      if (editMode==0) {
        if (editRaw==0) {
          if (Controller.firePressed()) loadSong();
          else saveSlot=max(saveSlot-1,0);
        }
        if (editRaw==1) {
          syncMode=constrain(syncMode-1,0,3);
        }
        if (editRaw==2) {
          if (Controller.firePressed()) swing--;
          else nbFrames--;
          nbFrames=constrain(nbFrames,0,32); 
          swing=constrain(swing,0,nbFrames);
        }
        if (editRaw==3) {
          if (Controller.firePressed()) {
            nbFrames=constrain(round(nbFrames*2),0,32);
            swing=constrain(round(swing*2),0,nbFrames);            
            frameMs=constrain(round(frameMs/2),0,100);
          }
          else frameMs=constrain(frameMs-1,0,100);
        }
        if (editRaw==4) {
          geShiftNot=constrain(geShiftNot+1,-NBBEATS,NBBEATS);
        }
        if (editRaw==5) {
          geShiftDur=constrain(geShiftDur+1,-NBBEATS,NBBEATS);
        }
        if (editRaw==6) {
          geShiftCom=constrain(geShiftCom+1,-NBBEATS,NBBEATS);
        }
        if (editRaw==7) {
          geShiftVal=constrain(geShiftVal+1,-NBBEATS,NBBEATS);
        }
        if (editRaw==8) {
          if (Controller.firePressed()) geFxAct=false;
          else geFxSelect=(geFxSelect-1+NBCOMMANDS)%NBCOMMANDS;
        }
        if (editRaw==9) {
          if (Controller.firePressed()) geRtAct=-1;
          else geRtLength=max(geRtLength-1,1);
        }
        if (editRaw==10) {
          if (Controller.firePressed()) seqFxAct=false;
          else seqFxMode=max(seqFxMode-1,0);
        }        
        if (editRaw==11) {
          if (Controller.firePressed()) generateRandom(rndMode);
          else rndMode=max(rndMode-1,0);
        }
        if (editRaw==12) {
          if (Controller.firePressed()) geTrans=constrain(geTrans-12,-48,48);
          else geTrans=constrain(geTrans-1,-48,48);
        }
        if (editRaw==13) {
          if (Controller.firePressed()) copySel=pasteSel;
          else pasteSel=max(pasteSel-1,0);
        }
      }
      if (editMode==1) {
        int shiftBy = -(1+(11*Controller.firePressed()));        
        if (Controller.downPressed()) {
          for (int i=0;i<NBBEATS;i++) {
            if (notes[i]+shiftBy>=0) notes[i]+=shiftBy;
            else while(notes[i]-shiftBy<NBFREQS) notes[i]-=shiftBy;
          }
        }
        else {
          if (notes[editRaw]+shiftBy>=0) notes[editRaw]+=shiftBy;
          else while(notes[editRaw]-shiftBy<NBFREQS) notes[editRaw]-=shiftBy;
        }
      }
      if (editMode==2) {
        if (Controller.firePressed()) durations[editRaw]=0;
        else durations[editRaw]=(durations[editRaw]-1+128)%128;
      }
      if (editMode==3 &&  Controller.firePressed()) commands[editRaw]=(commands[editRaw]-1+NBCOMMANDS)%NBCOMMANDS;
      if (editMode==3 && !Controller.firePressed()) values[editRaw]=(values[editRaw]-1+128)%128;
    }
    nbKeyPressed++;
  }
  if (nbKeyPressed==0) {
    keyPressedTime=0;
    retriggerTime=30;
  }
  else {
    retriggerTime=max(retriggerTime-1,5);
    keyPressedTime++;
  }
}









