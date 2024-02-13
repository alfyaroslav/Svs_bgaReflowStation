
tmElements_t tm;
uint8_t hh, mm, ss;
uint8_t hhR, mmR, ssR;
uint8_t Shms[4], Stat;
boolean initial = 1;
boolean NoClock = false;
long prevClock; 

float sx, sy, mx, my, hx, hy;
float sdeg, mdeg, hdeg, Fconst = 0.0174532925;
uint16_t osx, osy, omx, omy, ohx, ohy;
int16_t x0, x1, yy0, yy1;
uint16_t xpos; // x
uint16_t ypos; // y
bool Clock = false, Gt_Set = false, Svkl_L = false;  // Gt_Set=true;
static byte OldSek;
// ---------------------------------------------------
void SetPosClock () {
  xpos = -1 + myGLCD.getDisplayXSize() / 2;
  ypos = -1 + (myGLCD.getDisplayYSize() - 50) / 2;
  Serial.println(xpos);
}
// ---------------------------------------------------
void Zegar() {                      // рисуем циферблат
  SetPosClock();
  myGLCD.setColor(VGA_LIME);
  myGLCD.drawCircle(xpos, ypos, ypos - 1);
  myGLCD.drawCircle(xpos, ypos, ypos - 2);
  myGLCD.setColor(VGA_RED);
  myGLCD.drawCircle(xpos, ypos, ypos - 5);
  myGLCD.drawCircle(xpos, ypos, ypos - 6);
  for (int i = 0; i < 360; i += 30) {       // Draw 12 lines
    sx = cos((i - 90) * Fconst);  
    sy = sin((i - 90) * Fconst);  
    x0 = sx * (ypos - 6) + xpos;
    yy0 = sy * (ypos - 6) + ypos;
    x1 = sx * (ypos - 22) + xpos;
    yy1 = sy * (ypos - 22) + ypos;
    myGLCD.drawLine(x0, yy0, x1, yy1);
  }
  myGLCD.setColor(VGA_WHITE);
  for (int i = 0; i < 360; i += 6) {        // Draw 60 dots
    sx = cos((i - 90) * Fconst);
    sy = sin((i - 90) * Fconst);
    x0 = sx * (ypos - 22) + xpos;
    yy0 = sy * (ypos - 22) + ypos;
    // Draw minute markers
    myGLCD.drawPixel(x0, yy0);
    // Draw main quadrant dots
    if (i == 0 || i == 90 || i == 180 || i == 270) myGLCD.fillCircle(x0, yy0, 4);
  }
  myGLCD.fillCircle(xpos, ypos, 7);
}
// --------------------------------------------
bool TikTime () {
   NoClock = true;
   if (!NoClock) {
     if (!RTC.read(tm)) {
        NoClock =!NoClock;
        ss = 0; mm = 0; hh = 0; OldSek = ss;
        prevClock = millis();
        Serial.println(" не прочитались часы");      
        }
     else {
        if (OldSek == tm.Second) return(false);
        ss = tm.Second;             // Advance second
        OldSek = ss;
        mm = tm.Minute;             // Advance minute
        hh = tm.Hour;               // Advance hour 
        return(true);
        }
   } 
     else {
     if ((millis() - prevClock) > 1000) {
       prevClock = millis();
       if (ss++ >= 59) { ss = 0;
         if (mm++ >= 59) { mm = 0;
           if (hh++ >= 11) hh = 0; }
       return(true);    
       }    
      } else return(false);  
     } 
}
// --------------------------------------------
void ClockSet () {
   tm.Hour = hhR;
   tm.Minute = mmR;
    //tm.Second = Shms[2];
   RTC.write(tm);    // Записываем время в модуль:
}

// --------------------------------------------
void StelsViev (uint8_t hhv, uint8_t mmv, uint8_t ssv) {
    sdeg = ssv * 6;                     // 0-59 -> 0-354
    mdeg = mmv * 6 + sdeg * 0.01666667; // 0-59 -> - includes seconds, but these increments are not used
    hdeg = hhv * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds, but these increments are not used
    hx = cos((hdeg - 90) * Fconst);
    hy = sin((hdeg - 90) * Fconst);
    mx = cos((mdeg - 90) * Fconst);
    my = sin((mdeg - 90) * Fconst);
    sx = cos((sdeg - 90) * Fconst);
    sy = sin((sdeg - 90) * Fconst);
    myGLCD.setColor(VGA_BLACK);

  if (ssv == 0 || initial) {
    initial = false;

    // Erase hour and minute hand positions every minute
    myGLCD.drawLine(ohx, ohy, xpos, ypos);
    ohx = hx * (ypos / 2) + xpos + 1;
    ohy = hy * (ypos / 2) + ypos;
    myGLCD.drawLine(omx, omy, xpos, ypos);
    omx = mx * (ypos / 2 + 30) + xpos;
    omy = my * (ypos / 2 + 30) + ypos;
  }
  // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
  myGLCD.drawLine(osx, osy, xpos, ypos);
  osx = sx * (ypos / 2 + 40) + xpos + 1;
  osy = sy * (ypos / 2 + 40) + ypos;

  if (Stat==2) myGLCD.setColor(VGA_ORAN);
    else myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(ohx, ohy, xpos, ypos);  // часовая стрелка

  if (Stat==1) myGLCD.setColor(VGA_ORAN);              
    else myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(omx, omy, xpos, ypos);  // минутная стрелка
  
  myGLCD.setColor(VGA_RED);
  myGLCD.drawLine(osx, osy, xpos, ypos); // секундная стрелка
  myGLCD.fillCircle(xpos, ypos, 7);
}
// --------------------------------------------
void Pr_Stels () {                  //  движение стрелок в часах
  if (!TikTime()) return;
  
  StelsViev (hh, mm, ss);
}
// --------------------------------------------
void Pr_StelsR () {                  //  движение стрелок в часах
  
    if (!TikTime()) return;
    ssR = ss;
    StelsViev (hhR, mmR, ssR);
    
  }
// --------------------------------------------
void SetTimClock () {
  hhR = hh; mmR = mm; ssR = ss;
}
