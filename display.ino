
void displaying() {
  if (currentFrame==0 || (seqFxAct && seqFxMode==0)) {
    if (editMode==0) {
      tv.clear_screen();
      displayMap();
      for (int i=0;i<NBPARAMS;i++) {
        if (i==editRaw) tv.draw_line(0,10+i*5,3,10+i*5,1);
        else tv.draw_line(2,10+i*5,3,10+i*5,1);
      }
      // load/save
      for (int i=0;i<NBSLOTS;i++) {
        if (i==saveSlot) tv.draw_line(8+i*5,8+0*5,8+i*5,12+0*5,1);
        else tv.set_pixel(8+i*5,10+0*5,1);        
      }
      // play/stop/tap/sync
      for (int i=0;i<4;i++) {
        if (i==syncMode) tv.draw_line(8+i*5,8+1*5,8+i*5,12+1*5,1);
        else tv.set_pixel(8+i*5,10+1*5,1);
      }
      // number frames / swing
      tv.draw_line(5,10+2*5,5+nbFrames,10+2*5,1);
      tv.draw_line(5+nbFrames+5,10+2*5,5+nbFrames+5+swing,10+2*5,1);
      // frame length / compensate frame (TODO)
      tv.draw_line(5,10+3*5,5+frameMs,10+3*5,1);
      // shift notes / activate
      tv.draw_line(5+50,10+4*5,5+50-geShiftNot*3,10+4*5,1);
      // shift durations / activate
      tv.draw_line(5+50,10+5*5,5+50-geShiftDur*3,10+5*5,1);
      // shift commands / activate
      tv.draw_line(5+50,10+6*5,5+50-geShiftCom*3,10+6*5,1);
      // shift values / activate
      tv.draw_line(5+50,10+7*5,5+50-geShiftVal*3,10+7*5,1);
      // global effect / activate
      for (int i=0;i<NBCOMMANDS;i++) {
        if (i==geFxSelect) tv.draw_line(8+i*5,8+8*5,8+i*5,12+8*5,1);
        else tv.set_pixel(8+i*5,10+8*5,1);
        drawSymbol(8+NBCOMMANDS*5, 8+8*5, 3, 3, geFxSelect*3);
        if (geFxAct) tv.draw_line(8+(NBCOMMANDS+1)*5,8+8*5,8+(NBCOMMANDS+1)*5,12+8*5,1);
      }
      // retrigger length / activate
      for (int i=0;i<NBBEATS;i++) {
        if (geRtAct>-1) {
          if (i==geRtAct+geRtStart) tv.draw_line(8+i*5,10+9*5,8+i*5,12+9*5,1);
          else if ((i>=geRtStart&&i<geRtStart+geRtLength)||(geRtStart+geRtLength>=NBBEATS&&i<(geRtStart+geRtLength)%NBBEATS)) tv.set_pixel(8+i*5,10+9*5,1);
        }
        else{
          if ((i>=geRtStart&&i<geRtStart+geRtLength)||(geRtStart+geRtLength>=NBBEATS&&i<(geRtStart+geRtLength)%NBBEATS)) tv.draw_line(8+i*5,10+9*5,8+i*5,12+9*5,1);
          else tv.set_pixel(8+i*5,10+9*5,1);
        }
      }
      if (geRtAct>-1) {
        tv.set_pixel(8+currentBeat*5,11+9*5,1);
      }
      // no new beat, limit octave range, invert durations, reverse / activate and release << TODO
      for (int i=0;i<4;i++) {
        if (i==seqFxMode) tv.draw_line(8+i*5,8+10*5,8+i*5,12+10*5,1);
        else tv.set_pixel(8+i*5,10+10*5,1);
        if (seqFxAct) tv.draw_line(8+4*5,8+10*5,8+4*5,12+10*5,1);
      }
      // randomize (notes,durations,commands,values,params,all) / trigger
      for (int i=0;i<6;i++) {
        if (i==rndMode) tv.draw_line(8+i*5,8+11*5,8+i*5,12+11*5,1);
        else tv.set_pixel(8+i*5,10+11*5,1);
      }
      // transpose / transpose octave
      tv.draw_line(5+64,10+12*5,5+64+geTrans,10+12*5,1);
      // copy / paste
      for (int i=0;i<NBBEATS;i++) {
        if (i==pasteSel) tv.set_pixel(5+i*5,9+13*5,1);
        if (i==copySel) tv.draw_line(5+i*5,11+13*5,5+i*5,10+13*5,1);
        if (i==currentBeat) tv.draw_line(5+i*5,12+13*5,5+i*5,10+13*5,1);
        tv.set_pixel(5+i*5,10+13*5,1);
      }
    }
    if (editMode==1) {// notes
      tv.clear_screen();
      displayMap();      
      tv.set_pixel(0, ((currentBeat+geShiftNot+16)%NBBEATS)*BEATYSIZE, 1);
      tv.draw_line(1+NBFREQS+1,0,1+NBFREQS+1,(NBBEATS+1)*BEATYSIZE,1);
      for (int i=0;i<NBBEATS;i++) {
        if (i==editRaw) tv.draw_line(1, i*BEATYSIZE, 1+notes[i]+1, i*BEATYSIZE, 1);
        else tv.set_pixel(1+notes[i]+1, i*BEATYSIZE, 1);
      }
      printNoteAt(notes[editRaw], notes[editRaw]+5, editRaw*BEATYSIZE);
      printNoteAt(notes[(currentBeat+geShiftNot+16)%NBBEATS],32, (NBBEATS+1)*BEATYSIZE);      
    }
    if (editMode==2) {// durations
      tv.clear_screen();
      displayMap();      
      tv.set_pixel(0, currentBeat*BEATYSIZE, 1);
      tv.draw_line(1+128+1,0,1+128+1,(NBBEATS+1)*BEATYSIZE,1);
      tv.draw_line(1+nbFrames-swing+1,(NBBEATS+1)*BEATYSIZE,1+nbFrames-swing+1,(NBBEATS+2+    ((editRaw+geShiftDur)%2))*BEATYSIZE,1);
      tv.draw_line(1+nbFrames+swing+1,(NBBEATS+1)*BEATYSIZE,1+nbFrames+swing+1,(NBBEATS+2+(1-((editRaw+geShiftDur)%2)))*BEATYSIZE,1);      
      for (int i=0;i<NBBEATS;i++) {
        if (i==editRaw) tv.draw_line(1, i*BEATYSIZE, 1+durations[i]+1, i*BEATYSIZE, 1);
        else tv.set_pixel(1+durations[i]+1, i*BEATYSIZE, 1);
      }
    }
    if (editMode==3) {// commands
      tv.clear_screen();
      displayMap();      
      tv.set_pixel(0,   ((currentBeat+geShiftCom+16)%NBBEATS)*BEATYSIZE, 1);
      tv.set_pixel(W-1, ((currentBeat+geShiftVal+16)%NBBEATS)*BEATYSIZE, 1);
      for (int i=0;i<NBBEATS;i++) {
        drawSymbol(W-5, i*BEATYSIZE,3,3,commands[i]*3);
      }
      for (int i=0;i<NBBEATS;i++) {
        if (i==editRaw) {
          if (commands[i]==1 || commands[i]==2) tv.draw_line(66, i*BEATYSIZE, 1+values[i]+1, i*BEATYSIZE, 1);
          else if (commands[i]==5) {
            tv.draw_line(1 , i*BEATYSIZE, 1 +((values[i]>>0)&0b00001111)+1, i*BEATYSIZE, 1);
            tv.draw_line(20, i*BEATYSIZE, 20+((values[i]>>4)&0b00001111)+1, i*BEATYSIZE, 1);
          }
          else tv.draw_line(1, i*BEATYSIZE, 1+values[i]+1, i*BEATYSIZE, 1);
        }
        else {
          tv.set_pixel(1+values[i]+1, i*BEATYSIZE, 1);
        }
      }
    }
    if (editMode==4) {// visu
      visuPos+=commands[currentBeat];
      for (int i=0;i<8;i++) {
        tv.set_pixel((visuPos+notes[currentBeat])%W,(visuPos+durations[currentBeat])%H,values[currentBeat]%3);
        tv.set_pixel((visuPos+values[currentBeat])%W,(visuPos+notes[currentBeat])%H,durations[currentBeat]%3);
        tv.set_pixel((visuPos+durations[currentBeat])%W,(visuPos+values[currentBeat])%H,notes[currentBeat]%3);
      }
    }
  }
}

void displayMap() {
  for (int i=0;i<EDITMODES;i++) {
    if (i==editMode) tv.draw_line(0,H-12+i*2,3,H-12+i*2,1);
    else tv.set_pixel(0,H-12+i*2,1);
  }
  if (Controller.upPressed())    tv.set_pixel(18,H-12,1);
  if (Controller.downPressed())  tv.set_pixel(18,H-8,1);
  if (Controller.leftPressed())  tv.set_pixel(16,H-10,1);
  if (Controller.rightPressed()) tv.set_pixel(20,H-10,1);
  if (Controller.firePressed())  tv.set_pixel(18,H-10,1);  
}

void drawSymbol(byte x, byte y, byte w, byte h, unsigned int bitmapIndex) {
  for (int y2=0;y2<h;y2++) {
    const prog_uint8_t *index = symbols + bitmapIndex + y2;
    unsigned int theSymbol = pgm_read_word(index);
    for (int x2=0;x2<w;x2++) {
      if (0x001 & theSymbol>>(w-x2-1)) tv.set_pixel(x+x2,y+y2,1);
    }
  }
}

void printNoteAt(int n, int x, int y) {
  int nn = (n+11)%12;
  int no = floor((n+11)/12);
  if (nn==0) drawSymbol(x,y,3,3,15*3);
  if (nn==1) drawSymbol(x,y,3,3,15*3);
  if (nn==2) drawSymbol(x,y,3,3,16*3);
  if (nn==3) drawSymbol(x,y,3,3,16*3);
  if (nn==4) drawSymbol(x,y,3,3,17*3);
  if (nn==5) drawSymbol(x,y,3,3,18*3);
  if (nn==6) drawSymbol(x,y,3,3,18*3);
  if (nn==7) drawSymbol(x,y,3,3,19*3);
  if (nn==8) drawSymbol(x,y,3,3,19*3);
  if (nn==9) drawSymbol(x,y,3,3,20*3);
  if (nn==10) drawSymbol(x,y,3,3,20*3);
  if (nn==11) drawSymbol(x,y,3,3,21*3);
  if (nn==1||nn==3||nn==6||nn==8||nn==10) drawSymbol(x+4,y,3,3,14*3);
  for (int i=0;i<no;i++) {
    tv.set_pixel(x+8+i%3,y+floor(i/3),1);
  }
}




