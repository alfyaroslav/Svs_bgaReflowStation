//Релиз от 06,03,2023    Ver.10.2
#include "ASetting.h"
// Используемые библиотеки -----------------------------
#include <stdint.h>
#include <RotaryEncoder.h>
#if defined(__AVR__)
#include <UTFT.h>
#include "Cl_do_btn_long.h"
#include <Wire.h>
#include <TimeLib.h>
#elif defined(ESP8266) || defined(ESP32)
#include <TimeLib32.h>
#include <TFT_CONV.h>
#include "SPIFFS.h"
#include "FS.h"
#include <SPI.h>
//include "HardwareSerial.h"
#endif
#include <DS1307RTC.h>
#include <EEPROM.h>

#if defined(__AVR__)
 UTFT myGLCD(ILI9488_8, 38, 39, 40, 41);
// UTFT myGLCD(ILI9481, 38, 39, 40, 41);
#elif defined(ESP8266) || defined(ESP32)
 TFT_CONV myGLCD;
#endif

#include "SddPicture.h"
//--------------------------------------------
#ifndef SetEnglish
  #include "ConstProgm.h"
#else
  #include "ConstProgmEN.h"
#endif
//-------- кнопки ----------------------------
#include "Batton1.h"
// -------- TouchScreen ----------------------
#include "Touch.h"
// -------- энкодер --------------------------
#include "Encoder.h"
//--------- Temp -----------------------------
#include "Temp6675.h"
//-----------Peremen.h------------------------
#include "Peremen.h"
//--------------------------------------------
#include "Clock.h"
//--------------------------------------------
#include "Gvard.h"
//--------------------------------------------
#include "GyverButton.h"
GButton myButt1;
GButton myButtUp;
GButton myButtDOWN;
GButton myButtLeft;
GButton myButtRight;
GButton myButtOk;
//--------------------------------------------
void *Wr_mem, *Wr_pr;
int WrPerm, WrMemo;
char *Ad_tekct;
// -----------------
bool F_timK = false;
//
boolean RetGr;
int Pr_Line_M[10][4];

#if defined(ESP8266) || defined(ESP32)
hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR()
{
    Dimming();
}
#endif

// ------------------------------ 
void Pr_WinTime() {   // -------------для замера времени ------------
  //Serial.print("time - ");
  //Serial.println(micros() - WinStartTime);
}
// ------------------
void ChangeState(reflowState_t ChSt, bool UpScr) {
   reflowState = ChSt;
   updateScreen = UpScr;  
}
// ------------------
void Pr_Line_Load(int i_i, int X_St, int Y_St, int X_En, int Y_En) {
  Pr_Line_M[i_i][0] =  X_St;
  Pr_Line_M[i_i][1] =  Y_St;
  Pr_Line_M[i_i][2] =  X_En;
  Pr_Line_M[i_i][3] =  Y_En;
}
// -----------------
double M_tg_Line(int i_i) {
  double Tg_ugla;
  Tg_ugla = 0;
  if (Pr_Line_M[i_i][2] != Pr_Line_M[i_i][0]) {
    Tg_ugla = Pr_Line_M[i_i][3] - Pr_Line_M[i_i][1];
    Tg_ugla = Tg_ugla / (Pr_Line_M[i_i][2] - Pr_Line_M[i_i][0]);
  }
  // Serial.print("Tg - "); Serial.println(Tg_ugla);
  return (Tg_ugla);
}
// -----------------
void M_ln_point (int X_tec, int XxSt, int YySt, int XxEn, int YyEn) {  // вывод линии попиксельно
  float Tg_ugla;
  if (X_tec - X_graf <= XxSt + 1 || X_tec - X_graf > XxEn + 1) return;
  // Serial.print(XxSt);  Serial.print("  ");  Serial.print(YySt);  Serial.print("  ");
  // Serial.print(XxEn);  Serial.print("  ");  Serial.println(YyEn);
  if (YySt == YyEn) {
    myGLCD.drawPixel(X_tec - 1, Y_graf - YySt);
    return;
  }
  float B_1 = XxEn - XxSt;
  float A_1 = YyEn - YySt;
  if (B_1 != 0) Tg_ugla = A_1 / B_1;
  else Tg_ugla = 0;                 // 30, 40, 210, 145
  int tt = Y_graf - (YySt + (X_tec - X_graf - XxSt) * Tg_ugla);
  // Serial.print(Tg_ugla,6);  Serial.print("  ");  Serial.println(tt);
  myGLCD.drawPixel(X_tec - 1, tt + 1);
  return;
}
// --------------------------------------------
void M_dr_line (int XxSt, int YySt, int XxEn, int YyEn) {   // рисуем линию на графике
  myGLCD.drawLine(X_graf + XxSt, Y_graf - YySt, X_graf + XxEn, Y_graf - YyEn);
  return;
}
// --------------------------------------------
void M_dr_point (int XxSt, int YySt) {                      // рисуем точку на графике
  myGLCD.drawPixel(X_graf + XxSt, Y_graf - YySt);
  return;
}
// --------------------------------------------
void M_dr_int (int IiInt, int XxSt, int YySt) {             // пишем число на графике
  myGLCD.printNumI(IiInt, X_graf + XxSt, Y_graf - YySt, 3);
  return;
}
//---------------------------------------------
void ButRight() {   //    "Button - RIGHT"
  switch (reflowState) {          //  переключатель состояния
    case REFLOW_STATE_IDLE:  ChangeState(REFLOW_STATE_PROFILE, 1); 
      break;
    case REFLOW_STATE_PROFILE: {
      ChangeState(REFLOW_STATE_SETTING,1);
      RetGr = true;
      } 
      break;
    case REFLOW_STATE_SETTING: {
      if (Vklad_G == 1 && Shag < 3) {
        Shag += 1;
        return;
      }
      Shag = 0;  Shag_old = 0;
      Vklad_G += 1;
      if (Vklad_G >= Win1) Vklad_G = 0;
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT: {
      if (Stat > 1) Stat = 1;
        else  Stat = 2;        
      }
      break;
    case REFLOW_STATE_PROFILE_LOAD: {
      if (Stat < 2) Stat += 1;
        else Stat = 1;
      Obsi2_Old = 15;  
      }
      break;
    } // end switch
}
//---------------------------------------------
void ButUp()    {    //    "Button - UP"
  switch (reflowState) {          //  переключатель состояния
    case REFLOW_STATE_IDLE: {
      currentProfile = currentProfile + 1;
      if (currentProfile > numMax)  currentProfile = 1;
      loadProfile(currentProfile);
      VievTemp();
      PrPrint(B_SetX + 2, T_SetY);
      }
      break;
    case REFLOW_STATE_SETTING: {
      Vklad_L -= 1;
      if  (Vklad_G == 1) {
        if (Vklad_L < 1) Vklad_L = Win2 - 1;
        Shag_old = 9;
        }
      else if (Vklad_L < 0) Vklad_L = Win2 - 1;
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT: {
//     Serial.print("Stat = "); Serial.println(Stat);
     if (Stat == 1) {
      if (mmR < 59) mmR++;
        else { 
          mmR = 0; 
          if (hhR < 11) hhR++; 
            else hhR = 0;
        }
      }  
     if (Stat == 2) {
       if (hhR < 11) hhR++; 
            else hhR = 0;
      }
     initial = true; 
     Pr_StelsR();
      }
      break;
    case REFLOW_STATE_SET_EDIT: {
      ByteMax = 255;
      if (Vklad_G==0 || Vklad_G==1) {
        if (Vklad_G==0 && Vklad_L==0) ByteMax = 3;
        if (Vklad_G==0 && Vklad_L==2) ByteMax = 450;
        if (Vklad_L==1) ByteMax = 30;
        if (Vklad_L==4 || Vklad_L==5) ByteMax = 99;
        } 
       if (Vklad_G==3 && Vklad_L==0)  ByteMax = 1;    
       if (Vklad_G==3 && (Vklad_L==3 || Vklad_L==5))  ByteMax = 99; 
        if (ByteMax == 3 && Edit_Byte == ByteMax) {
         Edit_Byte = 1;
         break;
         }
        if (Edit_Byte < ByteMax) Edit_Byte += 1;
          else Edit_Byte = 0;  
    }
      break;
    case REFLOW_STATE_PROFILE: {
      currentProfile = currentProfile + 1;
      if (currentProfile > numMax)  currentProfile = 1;
      loadProfile(currentProfile);
      updateScreen = true;
      }
      break;
    case REFLOW_STATE_PROFILE_LOAD: {
      if(Stat == 1) { 
        if (ArObsi[1] < numMax) ArObsi[1] +=1;
          else ArObsi[1]=0;
        }
      }
      break;
    } // end switch
}  
//---------------------------------------------
void ButDown()  {    //    "Button - DOWN"
  switch (reflowState) {          //  переключатель состояния
    case REFLOW_STATE_IDLE: {
      currentProfile = currentProfile - 1;
      if (currentProfile < 1) currentProfile = numMax;
      loadProfile(currentProfile);
      VievTemp();
      PrPrint(B_SetX + 2, T_SetY);
      }
      break;
    case REFLOW_STATE_SETTING: {
      Vklad_L += 1;
      if (Vklad_G == 1) {
        if (Vklad_L >= Win2) Vklad_L = 1;
        Shag_old = 8;
      }
      else if (Vklad_L >= Win2) Vklad_L = 0;
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT: {
      if (Stat == 1) {
      if (mmR > 0) mmR--;
        else {
          mmR = 59;
          if (hhR>0) hhR--;
            else hhR=11;
          }
        }  
      if (Stat == 2) {
          if (hhR>0) hhR--;
            else hhR=11;
          }
      initial = true; 
      }
      break;
    case REFLOW_STATE_SET_EDIT: {
      ByteMax = 255;
      if (Vklad_G==0 || Vklad_G==1) {
        if (Vklad_G==0 && Vklad_L==0) ByteMax = 3;
        if (Vklad_G==0 && Vklad_L==2) ByteMax = 450;
        if (Vklad_L==1) ByteMax = 30;
        if (Vklad_L==4 || Vklad_L==5) ByteMax = 99;
        }     
      if (Vklad_G==3 && Vklad_L==0)  ByteMax = 1; 
      if (Vklad_G==3 && (Vklad_L==3 || Vklad_L==5))  ByteMax = 99; 
      if (ByteMax == 3 && Edit_Byte == 1) {
         Edit_Byte = ByteMax;
         break;
         }
      if (Edit_Byte != 0) {
        if (Edit_Byte <= ByteMax) Edit_Byte -= 1;
          else Edit_Byte = ByteMax;
        }
        else Edit_Byte = ByteMax;      
      }  
      break;
    case REFLOW_STATE_PROFILE: {
      currentProfile = currentProfile - 1;
      if (currentProfile < 1) currentProfile = numMax;
      loadProfile(currentProfile);
      updateScreen = true;
      }
      break;
    case REFLOW_STATE_PROFILE_LOAD: {
      if (Stat == 1) {
        if(ArObsi[1] == 0) ArObsi[1] = numMax;
          else ArObsi[1] -=1;
        }
      }
      break;
  } // end switch
}
//---------------------------------------------
void ButLeft()  {    //    "Button - LEFT"
  switch (reflowState) {          //  переключатель состояния
    case REFLOW_STATE_IDLE: {
      ChangeState(REFLOW_STATE_SETTING,1);
      RetGr = false;
      return;
      }
      break;
    case REFLOW_STATE_SETTING: {
      if (Vklad_G == 1 && Shag > 0) {
        if (Shag > 0)  Shag -= 1;
        break;
      }
      Vklad_G -= 1;
      if (Vklad_G < 0) {
        Vklad_G = 0;
        SaveProfile(currentProfile);
        if (RetGr == true) ChangeState(REFLOW_STATE_PROFILE,1);
          else ChangeState(REFLOW_STATE_IDLE,1);
        }
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT: {
      Ramka(5, VGA_BLACK);
      TimTouSet();
      Stat = 0;
      ChangeState(REFLOW_STATE_IDLE, 0);
      }
      break;
    case REFLOW_STATE_PROFILE: {
      ChangeState(REFLOW_STATE_IDLE,1);
      RetGr = false;
      }
      break;
    case REFLOW_STATE_BRAZE_NOW: ChangeState(REFLOW_STATE_BRAZE_STOP,1);
      break;
    case REFLOW_STATE_BRAZE_STOP: ChangeState(REFLOW_STATE_IDLE,1); 
      break;
    case REFLOW_STATE_PROFILE_LOAD: {
      if (Stat == 1) {
        ChangeState(REFLOW_STATE_SETTING,0);
        Vklad_L_old = 10;
        WinRamka (9, 105, 465, 209, VGA_BLACK, 1);
        myGLCD.fillRoundRect(320, Y_shift, 470, Y_shift+16);
        break;
        }
        else Stat -= 1;
       Obsi2_Old = 15;
      }
      break;
  } // end switch
} 
//---------------------------------------------
void ButOk()    {    //    "Button - OK"
  switch (reflowState) {          //  переключатель состояния
    case REFLOW_STATE_IDLE:  ChangeState(REFLOW_STATE_BRAZE_START,1);
      break;
    case REFLOW_STATE_SETTING: {   // переходим в режим редактирования
      if (Vklad_G == 3) {
        if (Vklad_L == 1) {
          ChangeState(REFLOW_STATE_PROFILE_LOAD,1);
          break;
          }
    //    if (Vklad_L == 0) {
    //      ChangeState(REFLOW_STATE_TIME_EDIT,1);
    //      break;   }
        }
      ChangeState(REFLOW_STATE_SET_EDIT,1);
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT: {
       if (Stat > 1) Stat = 1;
         else  Stat = 2;        
      }
      break;
    case REFLOW_STATE_SET_EDIT: {  // возврат в меню настроек после редактирования
      if (Vklad_G==0 && Vklad_L==2) *(int*)Wr_mem = Edit_Byte;
        else *(byte*)Wr_mem = Edit_Byte;
      Vklad_L_old = 10;
      if (Vklad_G == 1) Shag_old = 8;
      ChangeState(REFLOW_STATE_SETTING,0);
      WinRamka (9, 105, 465, 209, VGA_BLACK, 1); // 355, 240, 113, 69, VGA_BLACK, 1
      }
      break;
    case REFLOW_STATE_PROFILE: {
      Gt_Set = !Gt_Set;
      }
      break;
    case REFLOW_STATE_PROFILE_LOAD: {
      if (Stat == 2) {
        if (ArObsi[1] == 0) {
          for (i=1; i<=numMax; i++) {
            WrLoadPr(i, i);
            }
          currentProfile = 1;
          ArObsi[1] = 1;
          PrPrint(0, 2);
          }
         else { 
           WrLoadPr(currentProfile, ArObsi[1]);         
           PrPrint(0, 2);
           }
        currentProfile = ArObsi[1]; 
        loadProfile(currentProfile);  
        ChangeState(REFLOW_STATE_SETTING,0);
        Vklad_L_old = 10;
        WinRamka (9, 105, 465, 209, VGA_BLACK, 1);
        myGLCD.fillRoundRect(320, Y_shift, 470, Y_shift+16);
        }
      }
      break;
    }   // end switch
}
// --------------------------------------------
void TempRead() {                   //  чтение температуры
  if (Input1 == 0) Input1 = ReadCelsius(thermoCLK, thermoCS_T, thermoDO);
    else Input1 = Input1 * 0.8 + 0.2 * (ReadCelsius(thermoCLK, thermoCS_T, thermoDO) + Corect_T);
  if (Input2 ==0) Input2 = ReadCelsius(thermoCLK2, thermoCS_B, thermoDO2);
    else Input2 = Input2 * 0.8 + 0.2 * (ReadCelsius(thermoCLK2, thermoCS_B, thermoDO2) + Corect_B);
  tc1 = Input1;
  tc2 = Input2;
}
// --------------------------------------------
void VievTempGl() {
  if (Input1<0) {
    // myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERROR"), 12, 37);
  }
  else {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(VGA_SILVER);
    myGLCD.printNumI(tc1, 5, 20, 3, '0');
    myGLCD.setFont(BigFont);
    myGLCD.setFontAlt(BFontRu);

  }
  if (Input2<0) {
    // myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERROR"), 388, 37);
  }
  else {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(VGA_SILVER);
    myGLCD.printNumI(tc2, 380, 20, 3, '0');
    myGLCD.setFont(BigFont);
    myGLCD.setFontAlt(BFontRu);

  }
}
//---------------------------------------------
void ProfEdit_2() {                 //  начало экрана настроек
  Vklad_G = 0;
  Vklad_L = 0;
  myGLCD.clrScr();
  PrPrint(0, 2);
  Vklad_G_old = 15;
  Vklad_L_old = 15;
  Svkl_L = false;
  K_Kpres_ok = false;
  NewPos = 0; LastPos = 0;
  #ifdef SetEncoder 
    encoder.setPosition(0);
  #endif  
  updateScreen = false;
}
// --------------------------------------------
void Dimming() {
  OutPWR_TOP();
  OutPWR_BOTTOM();
}
// --------------------------------------------
void OutPWR_TOP() {
  reg1 = round(Output1) + er1; //pwr- задание выходной мощности в %,в текущем шаге профиля, er- ошибка округления
  if (reg1 < 50) {
    out1 = LOW;
    er1 = reg1; // reg- переменная для расчетов
  }
  else {
    out1 = HIGH;
    er1 = reg1 - 100;
  }
  digitalWrite(RelayPin1, out1); //пин через который осуществляется дискретное управление
}
//---------------------------------------------
void OutPWR_BOTTOM() {
  reg2 = round(Output2) + er2; //pwr- задание выходной мощности в %, er- ошибка округления
  if (reg2 < 50) {
    out2 = LOW;
    er2 = reg2; // reg- переменная для расчетов
  }
  else {
    out2 = HIGH;
    er2 = reg2 - 100;
  }
  digitalWrite(RelayPin2, out2); //пин через который осуществляется дискретное управление
}
//---------------------------------------------
byte Pid1(double temp, double ust, byte kP, byte kI, byte kd)   { // верх
  byte out = 0;
  static float ed = 0;
  e1 = (ust - temp); //ошибка регулирования
  p1 =  (kP * e1); //П составляющая
  integra = (integra < i_min) ? i_min : (integra > i_max) ? i_max : integra + (kI * e1) / 1000.0; //И составляющая
  d1 = kd * (e1 - ed); //Д составляющая
  ed = e1;
  out = (p1 + integra + d1 < u.Profili.min_pwr_TOPStep[currentStep-1])
        ? u.Profili.min_pwr_TOPStep[currentStep-1]
        : (p1 + integra + d1 > u.Profili.max_pwr_TOPStep[currentStep-1])
        ? u.Profili.max_pwr_TOPStep[currentStep-1] : p1 + integra + d1;
  return out;
}
//---------------------------------------------
byte Pid2(double temp, double ust, byte kP, byte kI, byte kd)   { // низ 
  byte out = 0;
  static float ed = 0;
  e2 = (ust - temp);   //ошибка регулирования
  p2 =  (kP * e2);     //П составляющая
  integra2 = (integra2 < i_min) ? i_min : (integra2 > i_max) ? i_max : integra2 + (kI * e2) / 1000.0; //И составляющая
  d2 = kd * (e2 - ed); //Д составляющая
  ed = e2;
  out = (p2 + integra2 + d2 < u.Profili.min_pwr_BOTTOM) ? u.Profili.min_pwr_BOTTOM : (p2 + integra2 + d2 > bottomMaxPwr) ? bottomMaxPwr : p2 + integra2 + d2;
  return out;
}
// --------------------------------------------
void Ramka(int i, word color) {
  myGLCD.setColor(color);
  if (i==5) {
    myGLCD.drawCircle(xpos, ypos, 50); 
   } else {
    myGLCD.drawRoundRect(BattSet[i][0], BattSet[i][1], BattSet[i][2], BattSet[i][3]);
    myGLCD.drawRoundRect(BattSet[i][0] + 1, BattSet[i][1] + 1, BattSet[i][2] - 1, BattSet[i][3] - 1);
   }
}
// --------------------------------------------
#if defined(__AVR__)
void printFromPGM (int charMap, int xx, int yy) {
  strcpy_P(buffer, pgm_read_word(charMap));
  myGLCD.print(buffer, xx, yy); 
}
#elif defined(ESP8266) || defined(ESP32)
void printFromPGM (const char * const * charMap, int xx, int yy) {
  strcpy_P(buffer, ((const char *)(charMap[0])) );
  myGLCD.print(buffer, xx, yy);
}
#endif

// --------------------------------------------
int stlenFromPGM (int charMap) {
  uint16_t ptr = pgm_read_word(charMap);
  int klen = 0, i = 0;
  //char c1 = 0xD0; char c2 = 0xD1;
  do {
    buffer[i] = (byte)(pgm_read_byte(ptr++));
    //Serial.println(buffer[i], HEX);
    if (buffer[i] != char(0xD0) && buffer[i] != char(0xD1)) klen++;
    } while (buffer[i++] != NULL);
  return(klen-1);
}
// --------------------------------------------
void VievTemp() {                   // вывод температуры профиля на главный экран
  // myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_SILVER);
  myGLCD.printNumF(u.Profili.rampRateBOTTOM * 0.1, 0, 383, 75);
  myGLCD.printNumF(u.Profili.rampRateStep[0] * 0.1, 0, 0, 75);
  j = 0;
  for (i = 0; i < 4; i++) {
    if (u.Profili.temperatureStep[i] > j) j = u.Profili.temperatureStep[i];
  }
  myGLCD.printNumI(j, 0, 95, 3, '0');
  myGLCD.printNumI(u.Profili.temperatureBOTTOM, 410, 95, 3, '0');
}
// --------------------------------------------
void GlabPrint() {                  // главный экран
  Clock = true;
  myGLCD.clrScr();
  Zegar();
  myGLCD.setColor(VGA_LIME);
  printFromPGM (&myText[0], 2, 2);   //x=22
  printFromPGM (&myText[1], RIGHT, 2);  //x=404
  myGLCD.setColor(VGA_SILVER);
  myGLCD.print(F("`"), 55, 95);
  myGLCD.print(F("`/с"), 50, 75);
  myGLCD.print(F("`"), 460, 95);
  myGLCD.print(F("`/с"), 432, 75);
  myGLCD.print(F("v10_2"), 304, 256);
  myGLCD.setColor(VGA_ORAN);
  if (ArObsi[4] != 0) {
    myGLCD.print(F("`"), 460, 115);
    myGLCD.printNumI(ArObsi[4], 410, 115, 3, ' ');
  }
  if (ArObsi[2] != 0) {    
    myGLCD.print(F("`"), 55, 115);
    myGLCD.printNumI(ArObsi[2], 0, 115, 3, ' ');
  }
  VievTemp();
  K_Kpres_ok = false;
  Stat = 0;
  initial = true; 
  PrPrint(B_SetX + 2, T_SetY);
  for (i = 0; i < 5; i++) {
    if (i == LastPos) Ramka( i, VGA_RED);
    else Ramka( i, VGA_SILVER);
  }
#ifdef Set_Picture
  myGLCD.drawBitmap(BattSet[1][0] + 10, BattSet[1][1] + 7, 68, 48, Graf, 1);
  myGLCD.drawBitmap(BattSet[0][0] + 10, BattSet[0][1] + 7, 68, 48, Graf2, 1);
  myGLCD.drawBitmap(BattSet[2][0] + 10, BattSet[2][1] + 7, 68, 48, Graf3, 1);
  myGLCD.drawBitmap(BattSet[3][0] + 10, BattSet[3][1] + 7, 68, 48, Graf4, 1);
#endif
  kluch = 0;
  updateScreen = false;
}
// --------------------------------------------
void PrPrint(int X, int Y) {        // номер и название профиля
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect(X, Y, 479 - X - 1, Y + 15);
  // myGLCD.setFont(BigFont);
  myGLCD.setColor(VGA_ORAN);
  myGLCD.printNumI(currentProfile, X, Y, 2);
  // myGLCD.setFont(BigFontRus);
  myGLCD.setColor(VGA_LIME);
  myGLCD.print(DuStr, X + 40, Y);
}
// --------------------------------------------
void DumpMem (byte NnProf) {        // читаем ПЗУ в СОМ порт

  // Для экономии места все Serial закомментированы
  // для печати на экран все комменты < // > убрать
  // и в функции loadProfile снять комменты с вызова DumpMem
  #ifdef Debug
    Serial.println("Читаем пзу ");
    String DuStr = "";
  #endif

  for (byte j = 0; j <= SizePrrof - 1; j++) {
    if (j % 10 == 0) {
      #ifdef Debug
        Serial.print(Adres+((NnProf-1)*SizePrrof)+j);
        Serial.print(" ");
      #endif
     }
     #ifdef Debug
       byte  DuBre = EEPROM.read(Adres + ((NnProf - 1) * SizePrrof) + j);
       Serial.print(DuBre);
       Serial.print(" ");
       if (j%10 == 9) Serial.println("");
     #endif

    if (j == ArrMax - 1) {
      #ifdef Debug
       Serial.println("");
      #endif   
      DuStr = String(u.Profili.HeadProf);
      #ifdef Debug
       Serial.println(DuStr);
       Serial.print(Adres+((NnProf-1)*SizePrrof)+j);
       Serial.print(" ");
      #endif 
    }

  }
  #ifdef Debug
    Serial.println("");
  #endif
}
// ------------------------------
void loadProfile(byte NnProf) {     //  загрузка текущего профиля
  DuStr = "";
  String DuVr;
  for (byte j = 0; j <= SizePrrof - 1; j++) {
    u.Mode[j] = EEPROM.read(Adres + ((NnProf - 1) * SizePrrof) + j);
  }
  for (j = 0; j < 6; j++) {
    ArObsi[j] = EEPROM.read(numMax*SizePrrof + Adres+1 + j);   
  }
  #ifdef Debug
    Serial.print(numMax*SizePrrof + Adres+1); Serial.print(" -"); Serial.println(ArObsi[j]);
  #endif

  DuVr = String(u.Profili.HeadProf);
  if (u.Mode[1] == 255)  DuStr += "НЕИЗВЕСТНЫЙ ПРОФИЛЬ " + String(NnProf) + " ";
  else {
    for (byte i = 0; i < ArrMax; i++) {
      if (DuVr.substring(i, i + 1) == "\0" || DuVr.substring(i, i + 1) == "\n") {
        DuStr += DuVr.substring(0, i+1);
        DuStr += "\0";
        i = ArrMax;
      }
    }
  }
  if (DuStr.length() == 0) DuStr += "НЕИЗВЕСТНЫЙ ПРОФИЛЬ " + String(NnProf) + " ";
  ArObsi[1] = NnProf;
   #ifdef Debug
    Serial.print(DuStr.length()); Serial.print(" -"); Serial.print(DuStr); Serial.println("-");
    DumpMem(NnProf);
   #endif
}
// --------------------------------------------
void SaveProfile(byte NnProf) {     //  сохранение текущего профиля
 #ifdef Debug
   Serial.print("SaveProfile >> "); Serial.println(NnProf);
 #endif
  for (byte j = 0; j <= SizePrrof - 1; j++) {    //j = ArrMax - 1  без заголовка
    #if defined(__AVR__)
      EEPROM.update(Adres + ((NnProf - 1)*SizePrrof) + j, u.Mode[j]);
    #elif defined(ESP8266) || defined(ESP32)
      EEPROM.write(Adres + ((NnProf - 1)*SizePrrof) + j, u.Mode[j]);
      EEPROM.commit();
    #endif
   }
  for (j = 0; j < 6; j++) {
     #if defined(__AVR__)
       EEPROM.update(numMax*SizePrrof + Adres+1 +j, ArObsi[j]);
     #elif defined(ESP8266) || defined(ESP32) 
       EEPROM.write(numMax*SizePrrof + Adres+1 +j, ArObsi[j]);
       EEPROM.commit();
     #endif    
  }
}
// --------------------------------------------
void In_Line(int t_start) {         //  рисуем профиль на графике
  int Temp_Start = t_start, Temp_End;
  int Time_Start = 0, Time_End;
  int Rt;
  // рисуем график температуры НИЗа
  myGLCD.setColor(VGA_RED);
  myGLCD.setFont(SmallFont);
  Temp_End = u.Profili.temperatureBOTTOM;
  Time_End = Time_Start + (10 * (Temp_End - t_start)) / u.Profili.rampRateBOTTOM;
  M_dr_line (Time_Start, Temp_Start, Time_End, u.Profili.temperatureBOTTOM);          // участок роста температуры
  Pr_Line_Load (0, Time_Start, Temp_Start, Time_End, u.Profili.temperatureBOTTOM);
  M_dr_int(u.Profili.dwellTimerBOTTOM, Time_End, u.Profili.temperatureBOTTOM - 3);    // надписи температуры и задержка
  M_dr_int(u.Profili.temperatureBOTTOM, Time_End - 26, u.Profili.temperatureBOTTOM + 10);
  Rt = Time_End;
  Time_End += u.Profili.dwellTimerBOTTOM;
  Time_Start = Time_End;
  Temp_Start = u.Profili.temperatureBOTTOM;

  // рисуем график температуры ВЕРХа по шагам
  myGLCD.setColor(VGA_ORAN);
  BrStepMax = 8;
  for (int i = 0; i < 4; i++) {
    if (u.Profili.rampRateStep[i] == 0) {
      BrStepMax = i * 2;
      break;
    }
    Temp_End = u.Profili.temperatureStep[i] - Temp_Start;
    if (Temp_End < 0) Temp_End = - Temp_End;
    Time_End = Time_Start + (10 * Temp_End) / u.Profili.rampRateStep[i];
    M_dr_line (Time_Start, Temp_Start, Time_End, u.Profili.temperatureStep[i]);
    Pr_Line_Load ((i + 1) * 2, Time_Start, Temp_Start, Time_End, u.Profili.temperatureStep[i]);

    M_dr_int(u.Profili.dwellTimerStep[i], Time_End, u.Profili.temperatureStep[i] - 3);
    M_dr_int(u.Profili.temperatureStep[i], Time_End - 26, u.Profili.temperatureStep[i] + 10);

    M_dr_line (Time_End, u.Profili.temperatureStep[i], Time_End + u.Profili.dwellTimerStep[i], u.Profili.temperatureStep[i]);
    Pr_Line_Load( (i + 1) * 2 + 1, Time_End, u.Profili.temperatureStep[i], Time_End + u.Profili.dwellTimerStep[i], u.Profili.temperatureStep[i]);
    Time_End += u.Profili.dwellTimerStep[i];
    Temp_Start = u.Profili.temperatureStep[i];
    Time_Start = Time_End;
  }
  myGLCD.setColor(VGA_RED);
  M_dr_line (Rt, u.Profili.temperatureBOTTOM, Time_Start, u.Profili.temperatureBOTTOM);    // горизонтальный участок низа
  Pr_Line_Load(1, Rt, u.Profili.temperatureBOTTOM, Time_Start, u.Profili.temperatureBOTTOM);
  myGLCD.setFont(BigFont);
  myGLCD.setFontAlt(BFontRu);

  /* for (i=0; i<10; i++) {    // вывод в порт массива
      Serial.print(i);
      Serial.print(" - ");
      for (int j=0; j<4; j++) {
       Serial.print(Pr_Line_M[i][j]);
       Serial.print("  ");
      }
      Serial.println("");
     } // */
}
// --------------------------------------------
void Sec_metr() {
  RTC.read(tm);
  if (OldSek != tm.Second) {
    OldSek = tm.Second;
    ss++;
    if (ss == 60) {
      ss = 0;
      mm++;
    }
    myGLCD.setColor(VGA_BLACK);
    myGLCD.fillRoundRect(432, TempY, 447, TempY + 16);
    // myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_SILVER);

    myGLCD.printNumI(mm, 400, TempY, 2, '0');
    myGLCD.printNumI(ss, 448, TempY, 2, '0');
   
  }
}
// --------------------------------------------
void Pr_Ramka_Y (int i) {           //  рисуем желтую рамку большую
  myGLCD.setColor(VGA_BLACK);     // стираем староое
  myGLCD.drawLine(0, Ywin1, 479, Ywin1);
  myGLCD.drawLine(0, Ywin1 - 1, 479, Ywin1 - 1);
  myGLCD.drawLine(0, Ywin1 - 2, 479, Ywin1 - 2);

  myGLCD.setColor(VGA_ORAN);   // рисуем желтую рамку большую
  myGLCD.drawLine(Xsize * i + 1, Yset + 1, Xsize * i + 1, Ywin1 - 1);
  myGLCD.drawLine(Xsize * i + 2, Yset + 1, Xsize * i + 2, Ywin1 - 2); //2
  myGLCD.drawLine(Xsize * i, Ywin1 - 2, 1, Ywin1 - 2);
  myGLCD.drawLine(Xsize * i, Ywin1 - 1, 0, Ywin1 - 1); //2
  myGLCD.drawLine(0, Ywin1 - 2, 0, 318);
  myGLCD.drawLine(1, Ywin1, 1, 318);                     //2
  myGLCD.drawLine(1, 319, 478, 319);
  myGLCD.drawLine(1, 318, 478, 318);                            //2
  myGLCD.drawLine(479, 318, 479, Ywin1 - 1);
  myGLCD.drawLine(478, 318, 478, Ywin1 - 1);               //2
  myGLCD.drawLine(479, Ywin1 - 2, Xsize * (i + 1) - 2, Ywin1 - 2);
  myGLCD.drawLine(478, Ywin1 - 1, Xsize * (i + 1) - 2, Ywin1 - 1); //2
  myGLCD.drawLine(Xsize * (i + 1) - 2, Ywin1 - 2, Xsize * (i + 1) - 2, Yset + 2);
  myGLCD.drawLine(Xsize * (i + 1) - 3, Ywin1 - 2, Xsize * (i + 1) - 3, Yset + 2); //2
  myGLCD.drawLine(Xsize * i + 2, Yset, Xsize * (i + 1) - 3, Yset);
  myGLCD.drawLine(Xsize * i + 1, Yset + 1, Xsize * (i + 1) - 2, Yset + 1); //2
}
// --------------------------------------------
void K_Setka() {
  myGLCD.setFont(SmallFont);
  for (i = 0; i <= K_line; i++)  {      // рисуем горизонтальные линии
    myGLCD.setColor(VGA_ORAN);         // 250, 180, 000
    myGLCD.printNumI((K_line - i) * 20, 0, Py_pr + i * 20 , 3); //,'0'
    myGLCD.setColor(30, 30, 30);
    myGLCD.drawLine(X_graf, Py_pr + 6 + i * 20, 479, Py_pr + 6 + i * 20);
  }
  myGLCD.setColor(VGA_ORAN);
  myGLCD.drawLine(X_graf - 3, Y_graf, 479, Y_graf);
  myGLCD.drawLine(X_graf - 3, Y_graf + 1, 479, Y_graf + 1);
  byte nn = 0;
  for (i = 0; i <= 14; i++)  {           // рисуем нижнюю шкалу
    myGLCD.drawLine(X_graf + i * 30, Y_graf - 6, X_graf + i * 30, Y_graf - 1);
    if (i > 0) nn = 4;
    if (i > 3) nn = 8;
    myGLCD.printNumI(i * 30, nn + 9 + i * 30, Y_graf + 4 , 3);
  }
  myGLCD.setFont(BigFont);
  myGLCD.setFontAlt(BFontRu);
}
// --------------------------------------------
void press_ok() {               // обработчик короткого  ok()
  if (reflowState == REFLOW_STATE_IDLE)       {
    switch (LastPos)   {
      case 0: {
          if (!K_Kpres_ok) {   // ButLeft переход в настройки
            ButLeft();
            K_Kpres_ok = true;
            Svkl_L = false;
          }
          break;
        }
      case 1: {
          if (!K_Kpres_ok) {   // ButRight переход к графикам профиля
            ButRight();
            K_Kpres_ok = true;
          }
          break;
        }
      case 2: {
          ButUp();
          break;
        }
      case 3: {
          ButDown();
          break;
        }
      case 4: {
          ButOk();
          break;
        }
    }
  }
  if (reflowState == REFLOW_STATE_SETTING)    {
    if (!Svkl_L && !K_Kpres_ok)  {
      Vklad_G_Mem = Vklad_G;
      SetStrL(true);
      Vklad_L = 0;
      if (Vklad_G == 1) Vklad_L = 1;
      NewPos = Vklad_L;
      #ifdef SetEncoder 
        encoder.setPosition(NewPos);
      #endif
      K_Kpres_ok = true;
    }
    if (Svkl_L && !K_Kpres_ok)  {     // переход в редактирование параметра
      Pos_Mem = LastPos;
      K_Kpres_ok = true;
      //NewPos = 2;
      //encoder.setPosition(NewPos);
      ButOk();
    }
  }
  if (reflowState == REFLOW_STATE_PROFILE)    {
    if (!K_Kpres_ok) {
      ButRight();
    }
  }
  if (reflowState == REFLOW_STATE_SET_EDIT)   {  // возврат в меню настроек после редактирования
    if (K_Kpres_ok) return;
    NewPos = Pos_Mem;
    #ifdef SetEncoder 
      encoder.setPosition(NewPos);
    #endif
    ButOk();
  }
  if (reflowState == REFLOW_STATE_PROFILE_LOAD)   {  // возврат в меню настроек загрузки профиля
    if (K_Kpres_ok) return;
    ButRight();
  }
  if (reflowState == REFLOW_STATE_CLOCK_EDIT) {
    ButOk();
    }
}
// --------------------------------------------
void longPress_ok() {           // обработчик длинного ok()
  if (reflowState == REFLOW_STATE_IDLE)       {
    if (LastPos == KnClock && !EnClSet) {
      Ramka(KnClock, VGA_RED);
      Stat = 1;
      EnClSet = true;
      ChangeState(REFLOW_STATE_CLOCK_EDIT, 1); 
    }
  }
  if (reflowState == REFLOW_STATE_CLOCK_EDIT && !EnClSet)       {
    Ramka(KnClock, VGA_BLACK);
    TimTouSet();
    Stat = 0;
    ClockSet();
    ChangeState(REFLOW_STATE_IDLE, 0);
  }
  if (reflowState == REFLOW_STATE_SETTING) {
    if (Svkl_L) {
      SetStrL(false);
      NewPos = Vklad_L;
      #ifdef SetEncoder 
        encoder.setPosition(NewPos);
      #endif  
      Shag_old = 10;
      if (Vklad_G == 1 && Vklad_L == 0) Vklad_L = 1;
    }
    else {
      Vklad_G = -1;
      NewPos = 0;
      ButLeft();
    }
  return;
  }
  if (reflowState == REFLOW_STATE_PROFILE || reflowState == REFLOW_STATE_BRAZE_NOW
      || reflowState == REFLOW_STATE_BRAZE_STOP  )    {
    Vklad_G = -1;
    NewPos = 0;
    ButLeft();
  }
  if (reflowState == REFLOW_STATE_PROFILE_LOAD)   {  // возврат в меню настроек загрузки профиля
    if (Stat == 2) ButOk();
      else ButLeft();
    }
}
// --------------------------------------------
void TimeLine(int XT) {
  byte hh = 0;
  if (XT > 50 && XT < 146) hh = 50;
  if (XT >= 146 && XT < 182) hh = 17;
  myGLCD.setColor(VGA_BLACK);
  myGLCD.drawLine(XT - 1, Py_pr + hh + 1, XT - 1, 263); // стираем старую таймлайн линию
  myGLCD.setColor(VGA_SILVER);     // 250, 180, 000
  myGLCD.drawLine(XT, Py_pr + hh + 1, XT, 263);  // рисуем новую
  myGLCD.setColor(30, 30, 30);     // VGA_SILVER
  for (i = 0; i < K_line; i++)  {                 // восстанавливаем сетку
    myGLCD.drawPixel(XT - 1, Py_pr + 6 + i * 20);
  }
  myGLCD.setColor(VGA_ORAN);
}
// --------------------------------------------
void SetStrL (bool Vk_L) {      // Боковая красная линия признак нахождения в нижнем меню
  Svkl_L = Vk_L;
  if (!Vk_L) myGLCD.setColor(VGA_BLACK);
  else myGLCD.setColor(VGA_RED);
  myGLCD.drawLine(3, Ywin1, 3, 316);
  myGLCD.drawLine(4, Ywin1, 4, 316);                     //2
  myGLCD.drawLine(5, Ywin1, 5, 316);
}
// --------------------------------------------
void TempBraze () {
  if (tc2<0) {
    // myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERORR"), 347, 217);    
    }
   else {
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.printNumI(tc2, 340, 200, 3, '0'); // выводим температуру низа
    myGLCD.setFont(BigFont);
    myGLCD.setFontAlt(BFontRu);

    }
  // myGLCD.setFont(BigFont);
  myGLCD.printNumI(Output2 , 440, 200, 2, '0'); // выводим мощность низа

  if (tc1<0) {
    // myGLCD.setFont(BigFont);
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ERORR"), 57, 47);
    }
   else { 
    if (TopStart == false)  myGLCD.setColor(VGA_SILVER);
    myGLCD.printNumI(Output1, 150, 30, 2, '0');   // выводим мощность верха
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.printNumI(tc1, 50, 30, 3, '0'); // выводим температуру верха
    myGLCD.setFont(BigFont);
    myGLCD.setFontAlt(BFontRu);

   }
}
// --------------------------------------------
void TonGo () {
  //Мелодия приветствия Марио
  tone(buzzerPin,1318,150);
  delay(150);
  tone(buzzerPin,1318,300);
  delay(300);
  tone(buzzerPin,1318,150);
  delay(300);
  tone(buzzerPin,1046,150);
  delay(150);
  tone(buzzerPin,1318,300);
  delay(300);
  tone(buzzerPin,1568,600);
  delay(600);
  tone(buzzerPin,784,600);
  delay(600);
  noTone(buzzerPin); 
 
}
// --------------------------------------------
void HeartPic () {
  #ifdef SetPicHeater
    myGLCD.drawBitmap(65, 135, 64, 64, Heater2, 1);
    #define SsPic1 150
    #define SsPic2 CENTER
  #else
    #define SsPic1 CENTER
    #define SsPic2 CENTER
  #endif
    myGLCD.setColor(VGA_GREEN);
    printFromPGM (&myText[12],SsPic2, 90);     //
    myGLCD.setColor(VGA_RED);
    myGLCD.print(F("ESP32"),SsPic1, 140);   //CENTER
    myGLCD.setColor(VGA_SILVER);
    myGLCD.print(F("Watashi Svs v10_2"),SsPic1, 175);

    delay(3000);   
  // TonGo();       //Мелодия приветствия Марио
}
// --------------------------------------------
void WinRamka (int KorX, int KorY, int DLX, int DLY, word Color, bool Clean) {
  if (Clean) {
     myGLCD.setColor(Color);
     myGLCD.fillRoundRect(KorX, KorY, KorX+DLX, KorY+DLY);
    }
    else {
      myGLCD.setColor(Color);  
      myGLCD.drawRoundRect(KorX, KorY, KorX+DLX, KorY+DLY);
      myGLCD.drawRoundRect(KorX+1, KorY+1, KorX+DLX-1, KorY+DLY-1); 
    }
}
// --------------------------------------------
void WrLoadPr (byte Pr_Out, byte Pr_In) {
  for (j=0; j<ArrMax; j++) u.Profili.HeadProf[j]=32;
  #if defined(__AVR__)
    strcpy_P(u.Profili.HeadProf, (char *)pgm_read_word(&(AdrProfN[Pr_In-1])));  //  пишем в буфер
  #elif defined(ESP8266) || defined(ESP32)
    strcpy_P(u.Profili.HeadProf, ((const char *)AdrProfN[Pr_In-1]));  //  пишем в буфер
  #endif
  for (j=1; j<=(SizePrrof-ArrMax); j++) {
    u.Mode[ArrMax+j-1] = pgm_read_byte_near(ProfDate[Pr_In-1]+j);
    } 
  SaveProfile(Pr_Out);
}
//---------------------------------------------
byte GetTempBot (int cont) {

  for (byte br=2; br<BrStepMax+2; br++) {
    if (cont > Pr_Line_M[1][TimeEnd_M]) {
      return(Pr_Line_M[BrStepMax+1][TempEnd_M]);
      }
    if (BrStepOld != br) { 
      BrTg2 = M_tg_Line(br);
      BrStepOld = br;      
      }
    if (Pr_Line_M[br][TimeSt_M] <= cont && Pr_Line_M[br][TimeEnd_M] > cont) { // если попадает в диапазон

     /*  Serial.print(br); Serial.print(" - "); Serial.print(BrTgTop); Serial.print(" -  ");
      Serial.print(Pr_Line_M[br][TimeSt_M]); Serial.print(" < "); Serial.print(cont); Serial.print(" > ");
      Serial.print(Pr_Line_M[br][TimeEnd_M]); // */ 
      
      if (Pr_Line_M[br][TempSt_M] == Pr_Line_M[br][TempEnd_M]) {    // если горизонтальный часток
        //Serial.print(" Tg "); Serial.println(Pr_Line_M[br][TempEnd_M]);
        return(Pr_Line_M[br][TempEnd_M]);
        }
        else {
          //Serial.print(" Tr "); Serial.println(Pr_Line_M[br][TempSt_M] + BrTg2 * (cont - Pr_Line_M[br][TimeSt_M]));
          return(Pr_Line_M[br][TempSt_M] + BrTg2 * (cont - Pr_Line_M[br][TimeSt_M]));
          }
      }
      //else return(0);  
  }
}
//---------------------------------------------
#ifdef SetTouch1
bool TouchGet() {
  tp = ts.getPoint();   // tp.x, tp.y считываем тач
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    xpok = map(tp.x, TS_LEFT, TS_RT, 0, DisXSize);
    ypok = map(tp.y, TS_TOP, TS_BOT, 0, DisYSize);
    //Serial.println("xpok = " + String(xpok) + "  ypok = " + String(ypok));
    return (true);
  }
  return (false);
}
#endif  
// --------------------------------------------
#ifdef SetTouch2
bool TouchGet() {
  #if defined(__AVR__)
    if (myTouch.dataAvailable() == true) {
      myTouch.read();
      xpok = myTouch.getX();
      ypok = myTouch.getY();
      if ((xpok != -1) || (ypok != -1))  {
         //xpok = 480 - xpok;   // если требуется разворот экрана на 180 гр
         //ypok = 320 - ypok;   // если требуется разворот экрана на 180 гр
         //Serial.print("Touch2 -");   Serial.print(xpok); Serial.print(" "); Serial.println(ypok);
        return (true);
        }
      }
    #elif defined(ESP8266) || defined(ESP32)
       uint16_t x, y;
       //int x, y;
       if (myGLCD.getTouch(&x, &y)) {
         xpok = x;
         ypok = y;
           //#ifdef Debug
           //  Serial.print("Touch2 -");   Serial.print(x); Serial.print(" "); Serial.println(y);
           //#endif 
           return (true); 
        }
    #endif
    return (false);
}
#endif
void TimTouSet() {
  TouchSet = millis() + 250; 
  return;
}
// --------------------------------------------
#ifdef Set_Touch
bool KnTouchGet(byte n) {
   if (xpok > BattSet[n][0] && xpok < BattSet[n][2] &&
       ypok > BattSet[n][1] && ypok < BattSet[n][3] ) return(true);
   return(false);
}
#endif
//       Pr_WinTime();    // на экран засеченное время в мсек
//       WinStartTime = micros();

// --------------------------------------------
void setup() {
  #if defined(ESP8266) || defined(ESP32)
     #define EEPROM_SIZE 2048
    EEPROM.begin(EEPROM_SIZE);
  #endif

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myGLCD.setFontAlt(BFontRu);
  Serial.begin(115200);

#ifdef SetTouch1
  SetPinTouch1();
    switch (Orientation) {      // adjust for different aspects
    case 0:   break;          //no change,  calibrated for PORTRAIT
    case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
    case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
    case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    } 
#endif
#ifdef SetTouch2
  #if defined(__AVR__)
    myTouch.InitTouch();
    myTouch.setPrecision(PREC_MEDIUM);
  #elif defined(ESP8266) || defined(ESP32)
    uint16_t calibrationData[5];
    uint8_t calDataOK = 0;
    // check file system
    if (!SPIFFS.begin()) {
      #ifdef Debug
        Serial.println("formating file system");
      #endif  
      SPIFFS.format();
      SPIFFS.begin();
    }

    // check if calibration file exists
    if (SPIFFS.exists(CALIBRATION_FILE)) {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calibrationData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
    if (calDataOK) {
      // calibration data valid
      myGLCD.setTouch(calibrationData);
    } else {
      // data not valid. recalibrate
      myGLCD.calibrateTouch(calibrationData, VGA_WHITE, VGA_RED, 20);
      // store data
      File f = SPIFFS.open(CALIBRATION_FILE, "w");
      if (f) {
        f.write((const unsigned char *)calibrationData, 14);
        f.close();
      }
    }
  #endif
  
#endif
  //setup pins as input for buttons
  pinMode (buzzerPin, OUTPUT);
  pinMode(P1_PIN, OUTPUT);
  digitalWrite(P1_PIN, SetReleOFF); 
  pinMode(P2_PIN, OUTPUT);
  digitalWrite(P2_PIN, SetReleOFF); 
  pinMode(P3_PIN, OUTPUT);
  digitalWrite(P3_PIN, SetReleOFF); 
  pinMode(P4_PIN, OUTPUT);
  digitalWrite(P4_PIN, SetReleOFF); 

  HeartPic ();
  #if defined(ESP8266) || defined(ESP32)
   SPI.begin();
  #endif
  Set_Pin_6675();             // настраиваем порты max6675
  //
  myButt1.setType(LOW_PULL);
  myButt1.setTimeout(2000);
  myButt1.setTickMode(MANUAL);

  myButtUp.setType(LOW_PULL);
  myButtUp.setTimeout(2000);
  myButtUp.setTickMode(MANUAL);
  
  //

  DisXSize = myGLCD.getDisplayXSize();
  DisYSize = myGLCD.getDisplayYSize();
  currentProfile = 1;
  loadProfile(currentProfile);
  Xsize = myGLCD.getDisplayXSize() / Win1;
  Y_S_win = (myGLCD.getDisplayYSize() - (Ywin0) - 2) / Win2;

  Y_shift = Ywin0 + (Y_S_win - 16) / 2;
  //setup ssr pins as outputs
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  digitalWrite(RelayPin1, LOW);
  digitalWrite(RelayPin2, LOW);

  #ifdef SetEncoder 
    encoder.setPosition(2 / ROTARYSTEPS); // start with the value of 1
  #endif
  nextRead1 = millis();
#ifdef SetInterrupt
  attachInterrupt(SetInterrupt, Dimming, RISING); // настроить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
  #if defined(__AVR__)
    MsTimer2::set(10, Dimming); // 100ms period
    MsTimer2::start();
  #elif defined(ESP8266) || defined(ESP32)  
    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 100000, true); // 100ms period
    timerAlarmEnable(Timer0_Cfg);
  #endif  
#endif
} // end  setup
// ------------------------------------------------------
void loop() {
#ifdef SetAnalogBatton
  int analog = analogRead(Knopki);
    myButtUp.tick(analog < SetUP+Debion && analog > SetUP-Debion); 
    if (myButtUp.isClick())  ButUp();
    if (reflowState == REFLOW_STATE_IDLE && Stat != 1 && Stat != 2 && myButtUp.isHolded()) {
      Ramka(5, VGA_RED);
      Stat = 1;
      ChangeState(REFLOW_STATE_CLOCK_EDIT, 1);
      return;  
      }
    myButtDOWN.tick(analog < SetDOWN+Debion && analog > SetDOWN-Debion);
    if (myButtDOWN.isClick()) ButDown();    
    myButtLeft.tick(analog < SetLEFT+Debion && analog > SetLEFT-Debion);
    if (myButtLeft.isClick()) ButLeft();        
    myButtRight.tick(analog < SetRIGHT+Debion && analog > SetRIGHT-Debion);
    if (myButtRight.isClick()) ButRight();        
    myButtOk.tick(analog < SetSELECT+Debion && analog > SetSELECT-Debion);
    if (myButtOk.isClick()) ButOk();
    if (reflowState == REFLOW_STATE_CLOCK_EDIT && myButtOk.isHolded()) longPress_ok();          
#endif

#ifdef SetDigitBatton
  Btn_UP.run(&ButUp, &longPr_MID);
  Btn_DWN.run(&ButDown, &longPr_MID);
  Btn_LFT.run(&ButLeft, &longPr_MID);
  Btn_RHT.run(&ButRight, &longPr_MID);
  Btn_MID.run(&ButOk, &longPr_MID);
#endif

#ifdef SetEncoder
  Btn_ok.run(&press_ok, &longPress_ok);              // опрашиваем кнопку энкодера
  
  encoder.tick();                                    // читаем енкодер
  NewPos = encoder.getPosition();
  // Serial.print(NewPos); Serial.print("  "); Serial.print(Svkl_L); Serial.print("  ");  Serial.println(reflowState);
  if (LastPos != NewPos) {
    if (reflowState == REFLOW_STATE_IDLE)       {
      if (NewPos > 5) {
        NewPos = 0;
        encoder.setPosition(NewPos);
      }
      if (NewPos < 0) {
        NewPos = 5;
        encoder.setPosition(NewPos);
      }
      if (NewPos == KnClock) {
        Ramka(LastPos, VGA_SILVER);
        Ramka(NewPos, VGA_SILVER);
      } else {
      if (LastPos == KnClock) Ramka(LastPos, VGA_BLACK);
       else Ramka(LastPos, VGA_SILVER);
      Ramka(NewPos, VGA_RED);
      }
      LastPos = NewPos;
    }
    if (reflowState == REFLOW_STATE_SETTING)    {
      if (!Svkl_L) {
        if (NewPos > 3) NewPos = 0;
        if (NewPos < 0) NewPos = 3;
        encoder.setPosition(NewPos);
        if (Vklad_G == 1) {
          //Serial.println(LastPos);
          if (Vklad_L == 0) Vklad_L = 1;
          if (NewPos > LastPos && Shag != 3) { Shag += 1; encoder.setPosition(LastPos); return; }
          if (NewPos < LastPos && Shag != 0) { Shag -= 1; encoder.setPosition(LastPos); return; }
          }
        Vklad_G = NewPos;
        Shag = 0;  Shag_old = 0;
        LastPos = NewPos;
        }
      else {      //Serial.print("тут1  ");
        K_Pos = 0;
        if (Vklad_G == 1) K_Pos = 1;
        if (NewPos > 5) NewPos = K_Pos;
        if (NewPos < K_Pos)  NewPos = 5;
        encoder.setPosition(NewPos);
        Vklad_L = NewPos;
        LastPos = NewPos;
        Vklad_L_old = 15;
        return;
      }
    }
    if (reflowState == REFLOW_STATE_PROFILE)    {
      if (NewPos > numMax) {
        NewPos = 1;
        encoder.setPosition(NewPos);
      }
      if (NewPos < 1) {
        NewPos = numMax;
        encoder.setPosition(NewPos);
      }
      currentProfile = NewPos;
      loadProfile(currentProfile);
      updateScreen = true;
      LastPos = NewPos;
    }
    if (reflowState == REFLOW_STATE_SET_EDIT)   {
      if (NewPos > LastPos) {
        ButUp();
        encoder.setPosition(LastPos);
        return;
      }
      if (NewPos < LastPos) {
        ButDown();
        encoder.setPosition(LastPos);
        return;
      }
    }
    if (reflowState == REFLOW_STATE_PROFILE_LOAD) {
      if (Stat != 2) {
        if (NewPos > numMax) NewPos = 0;
        if (NewPos < 0) NewPos = numMax;
        encoder.setPosition(NewPos);
        ArObsi[1] = NewPos;
        LastPos = NewPos;
       }
    }
    if (reflowState == REFLOW_STATE_CLOCK_EDIT) {
      if (NewPos > LastPos)  ButUp(); // 
      if (NewPos < LastPos)  ButDown();
      encoder.setPosition(LastPos);
     }  
   }
   else K_Kpres_ok = false;
#endif

#ifdef Set_Touch
  if (TouchGet()) {                                // обработка нажатия на тач
 // Serial.print("Touch2 -");   Serial.print(xpok, HEX); Serial.print(" "); Serial.println(ypok);
    if (reflowState == REFLOW_STATE_IDLE)       {
      for (i = 0; i < 5; i++) {
        if (KnTouchGet(i)) {
        if (TouOld != i) {
          TouOld = i;
          TimTouSet();
          Ramka(LastPos, VGA_SILVER);
          if (i!=5) Ramka(i, VGA_RED);
          LastPos = i; 
          #ifdef SetEncoder
            encoder.setPosition(i);
          #endif
          switch (i)   {
            case 0: {   // кнопка влево
                if (!T_KeyLeft_Old) {
                  T_KeyLeft_Old = true;
                  ButLeft();
                  i = 5;
                }
              }
              break;
            case 1: {   // кнопка вправо
                if (!T_KeyRight_Old) {
                  T_KeyRight_Old = true;
                  ButRight();
                } 
              }
              break;
            case 2: {   // кнопка вверх
                if (!T_KeyUp_Old) {
                  T_KeyUp_Old = true;
                  ButUp(); 
                }
              }
              break;
            case 3: {   // кнопка вниз   
                if (!T_KeyDown_Old) {
                  T_KeyDown_Old = true;
                  ButDown();
                  }
              }
              break;
            case 4: {   // кнопка Ок
                  if (!T_KeyOk) {
                  T_KeyOk = true;
                  ButOk();
                  }
                }
              break; 
/*            case 5: {   // кнопка Часы
                 if (!T_KeyClock) {
                   T_KeyClock = true;
                   TouchClock = millis();
                   return;
                   }
                  else {
                    if (millis()-TouchClock > 2000) {
                   Serial.println("часы Edit");
                      Ramka(5, VGA_RED);
                      T_KeyClock = false;
                      updateScreen = true;
                      reflowState = REFLOW_STATE_CLOCK_EDIT;                      
                     }
                  } 
                }            
              break; */     
          }  // end switch
           
         } 
        }        // end проверка одной кнопки 
      }         // конец цикла
      myButt1.tick(KnTouchGet(KnClock));  
      if (myButt1.state()) {
         TimTouSet();
         }
      if (myButt1.isHolded()) {
        Ramka(KnClock, VGA_RED);
        Stat = 1;
        ChangeState(REFLOW_STATE_CLOCK_EDIT, 1);
        return;
        }   
    }           // end STATE_IDLE
    if (reflowState == REFLOW_STATE_PROFILE)    {
      if (KnTouchGet(KnESC) && !T_KeyLeft_Old) {
        T_KeyLeft_Old = true;
        ButLeft();
        }
      if (KnTouchGet(KnEdUp) && !T_KeyUp_Old) {
        T_KeyUp_Old = true;
        TimTouSet();
        ButUp();
        return;
      }
      if (KnTouchGet(KnEdDown) && !T_KeyDown_Old) {
        T_KeyDown_Old = true;
        TimTouSet();
        ButDown();
        return;
      }
      if (xpok > 430 && xpok < 478 && ypok > 30 && ypok < 260 && !T_KeyRight_Old) {
        T_KeyRight_Old = true;
        ButRight();
      }
    }
    if (reflowState == REFLOW_STATE_BRAZE_NOW || reflowState == REFLOW_STATE_BRAZE_STOP)  {
      if (xpok > 0 && xpok < 40 && ypok > 30 && ypok < 300) ButLeft();
    }
    if (reflowState == REFLOW_STATE_SETTING)    {
      for (i = 0; i < Win1; i++)  {   // переключаем вкладки
        if (xpok > Xsize * i && xpok < Xsize * (i + 1) && ypok > 0 && ypok < Ywin0) {
          Vklad_G = i;
          #ifdef SetEncoder 
            encoder.setPosition(i);
          #endif  
          if (Vklad_G == 1) { 
              LastPos = 1; 
              #ifdef SetEncoder 
                encoder.setPosition(1); 
              #endif
          }
            SetStrL(false);
          break; 
        }
      }
      for (i = 0; i <= Win2; i++) {   // переключаем строки
        if (xpok > 40 && xpok < 355 && ypok > i * Y_S_win + Ywin0 && ypok < (i + 1)*Y_S_win + Ywin0) {
          if (Vklad_G == 1 && Shag <= 3 && !T_KeyNext && i == 0) {
            if (Svkl_L) {   
              T_KeyNext = true;
              SetStrL(false);
              LastPos = 0;
              Shag_old = 10;
              Vklad_L = 1;
              #ifdef SetEncoder 
                encoder.setPosition(1);
              #endif  
              break;
            }
            else {
              T_KeyNext = true;
              Shag += 1;
              if (Shag > 3)  Shag = 0;
              break;
            }
          }
          Vklad_L = i;
          #ifdef SetEncoder 
            encoder.setPosition(i);
          #endif  
          SetStrL(true);
          Vklad_L_old = 15;   
          //Shag_old = 10;
          break;
        }
      }
      if (KnTouchGet(KnEdit) && !T_KeyOk && !T_KeyRight_Old) {  // окно редактирования параметра
        T_KeyOk = true;
        TimTouSet();
        ButOk();
      }
      if (KnTouchGet(KnESC) && !T_KeyLeft_Old) { // выход в главное меню
        Vklad_G = 0;
        T_KeyLeft_Old  = true;
        ButLeft();
      }
    }
    if (reflowState == REFLOW_STATE_SET_EDIT)   {
      if (KnTouchGet(KnEdit) && !T_KeyOk) {
        TimTouSet();
        T_KeyOk = true;
        ButOk();
        return;
      }
      if (KnTouchGet(KnEdUp) && !T_KeyRight_Old) {
        T_KeyRight_Old = true;
        TimTouSet();
        ButUp();
        return;
      }
      if (KnTouchGet(KnEdDown) && !T_KeyLeft_Old) {
        T_KeyLeft_Old = true;
        TimTouSet();
        ButDown();
        return;
      }
      j=0;  w=0;
      for (i = 0; i < 10; i++) { 
        if (i>=5) { 
          j=Batt_Y+10; w=5;
          }
       // WinRamka (20+(i-w)*(Batt_X+10), 189+j, Batt_X, Batt_Y, VGA_SILVER, 0);
        if (!TouDec && xpok > 20+(i-w)*(Batt_X+10) && xpok < 20+Batt_X+(i-w)*(Batt_X+10) 
            && ypok > 189+j && ypok < 189+j+Batt_Y) {
              TouDec = true;
              TimTouSet();
              Edit_Byte = 10*Edit_Byte + i;
              ByteMax = 255;
              if (Vklad_G==0 && Vklad_L==2) ByteMax = 450;
              if ((Vklad_G==0 || Vklad_G==1) && (Vklad_L==4 || Vklad_L==5)) ByteMax = 99;
              if (Vklad_G==3 && (Vklad_L==3 || Vklad_L==5))  ByteMax = 99; 
              if (Edit_Byte > ByteMax)  Edit_Byte = i; 
              i=10;
            }
        }
       return; 
    }
    if (reflowState == REFLOW_STATE_CLOCK_EDIT) {           
      if (KnTouchGet(KnUp) && !T_KeyUp_Old) {
        T_KeyUp_Old = true;
        TimTouSet();
        ButUp();
        }
      if (KnTouchGet(KnDown) && !T_KeyDown_Old) {
        T_KeyDown_Old = true;
        TimTouSet();
        ButDown();
        }      
      if (KnTouchGet(KnClock)) {
        myButt1.tick(1);  
        if (myButt1.state())  TimTouSet();
        if (myButt1.isClick()) {  
            ButOk();
            return;
            }
        if (myButt1.isHolded()) {
            Ramka(KnClock, VGA_BLACK);
            TimTouSet();
            Stat = 0;
            ClockSet();
            ChangeState(REFLOW_STATE_IDLE, 0);
            return;                                        
            }
      }
    }   
    if (reflowState == REFLOW_STATE_PROFILE_LOAD)   {
      if (xpok > 0 && xpok < 30 && ypok > 30 && ypok < 300)  ButLeft();
      if (xpok > 420 && xpok < 479 && ypok > Y_shift - 4 && ypok < Y_shift +30 && !T_KeyOk) {  
        T_KeyOk = true;
        TimTouSet();
        Stat = 2;
        ButOk();
        }
      if (xpok > 425 && xpok < 479 && ypok > 267 && ypok < 320 && !T_KeyRight_Old) {
        T_KeyRight_Old = true;
        TimTouSet();
        ButUp();
        }
      if (xpok > 377 && xpok < 424 && ypok > 267 && ypok < 320 && !T_KeyLeft_Old) {
        T_KeyLeft_Old = true;
        TimTouSet();
        ButDown();
        }
      }
  }
  if (millis() > TouchSet) {
    TouOld = 10;
    TouDec = false;
    T_KeyUp_Old = false;
    T_KeyDown_Old = false;
    T_KeyNext = false;
    T_KeyOk = false;
    //T_KeyClock = false;
    T_KeyRight_Old = false;
    T_KeyLeft_Old = false;
    myButt1.tick(0);
    }
#endif

  switch (reflowState)              {          //  переключатель состояния
    case REFLOW_STATE_IDLE:         {          //  Главный экран
        if (updateScreen) GlabPrint();           //  настройка экрана Рабочий режим
          Pr_Stels();                              //  стрелки часов тикают
         
        if (millis() > nextRead1) {
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;
          TempRead();    //  считываем температуру
          VievTempGl();

#ifdef SetConnectPC        
        if (kluch == 4) {
          kluch = 0;
          sprintf (buf, "OK%03d%03d%03d%03d%03d\r\n", (Output1), (Output2), tc1, tc2, (1)); // profileName
          Serial.print(buf);
        }
        kluch++;
#endif
        }
        Output2 = 0;
        Output1 = 0;
      }
      break;
    case REFLOW_STATE_SETTING:      {          //  вход в меню настроек
        if (updateScreen) ProfEdit_2();        
       // myGLCD.setFont(BigFontRus);
        if (Vklad_G != Vklad_G_old) {       // рисуем заголовки страницы настроек
          for (i = 0; i < Win1; i++)  {
            if (Vklad_G != i) {             // рамки заголовка
              myGLCD.setColor(VGA_SILVER);
              myGLCD.drawRoundRect(Xsize * i + 1, Yset, Xsize * (i + 1) - 2, Ywin1);
              myGLCD.drawRoundRect(Xsize * i + 2, Yset + 1, Xsize * (i + 1) - 3, Ywin1 - 1);
            }
            if (Vklad_G == i) myGLCD.setColor(VGA_LIME);
            int Xset2 = 2;//TEST(Xsize - (stlenFromPGM(&myStr2[i]) * 16)) / 2;
            printFromPGM (&myStr2[i], Xsize * i + Xset2, Yset + (Ysize - 16) / 2); // текст в рамке
            Vklad_L_old = 15;
            Cln_st = true;
          }
          Pr_Ramka_Y(Vklad_G);    // рисуем желтую рамку
          Vklad_G_old = Vklad_G;
          Vklad_L = 0;
          if (Vklad_G == 1) { Shag = 0; Shag_old = 10; Vklad_L = 1;  }          
        }
        if (Vklad_L != Vklad_L_old || Shag != Shag_old) {       // пишем строки и заполняем данными
          K_Kpres_ok = false;
          for (i = 0; i < Win2; i++) { 
            if (Cln_st) {                   // очистка строки
              myGLCD.setColor(VGA_BLACK);
              myGLCD.fillRoundRect(10, i * Y_S_win + Y_shift, 460, i * Y_S_win + Y_shift + 16);
              if(i == 0) myGLCD.fillRoundRect(312, i * Y_S_win + Y_shift-5, 337, i * Y_S_win + Y_shift + 20);
            }                      
            if (Vklad_L == i) {             // выбранный адрес параметра и строки подсвечиваем зеленым цветом
              myGLCD.setColor(VGA_LIME);   
              Wr_mem = (byte*)Adresa[Vklad_G][i] + Shag;
              if (Vklad_G == 0 && i == 2) WrMemo = *(int*)Adresa[Vklad_G][i];
                else WrMemo = *((byte*)Adresa[Vklad_G][i]+ Shag);
              Gi = Vklad_G; Li = i;
              //Ad_tekct = pgm_read_word(&myStr3[Vklad_G][i]);
              //Ad_tekct = myStr3[Vklad_G][i];
              } else myGLCD.setColor(VGA_SILVER); 
            if (i == 0 && Vklad_G == 1) myGLCD.setColor(VGA_ORAN);              
              printFromPGM (&myStr3[Vklad_G][i], 10, i * Y_S_win + Y_shift);  // выводим текст названия параметра
            if (Shag != Shag_old && Vklad_G == 1) {
              myGLCD.setColor(VGA_ORAN);
              for (j = 0; j < 4; j++) {
                if (Shag == j) {              // выбор ШАГ ПРОФИЛЯ
                  myGLCD.setColor(VGA_RED);
                  myGLCD.setBackColor(VGA_GRAY);
                }
                myGLCD.printNumI(j + 1, j * 40 + 318, i * Y_S_win + Y_shift);
                myGLCD.setColor(VGA_ORAN);
                myGLCD.setBackColor(VGA_BLACK);
              }
              myGLCD.setColor(VGA_SILVER);  
              Shag_old = Shag;
              continue;
            }
              Wr_pr = (byte*)Adresa[Vklad_G][i] + Shag;             // достаем адрес параметра
              if (Vklad_G == 0 && i == 2) WrPerm = *(int*)Wr_pr;    // читам параметр
                else WrPerm = *(byte*)Wr_pr;
                
              if (i == 1 && Vklad_G < 2) myGLCD.printNumF(WrPerm * 0.1, 0, 286, i * Y_S_win + Y_shift);
                 else  if (i != 0 || Vklad_G != 1) myGLCD.printNumI(WrPerm, 286, i * Y_S_win + Y_shift, 3, ' ');
                  
            if (Vklad_G == 3 && i == 0) {         // печатаем галочку на вкладке "Общие"
              if (ArObsi[0] == 1) myGLCD.drawBitmap(312, i * Y_S_win + Y_shift-5, 25, 25, yes, 1);
                else myGLCD.drawBitmap(312, i * Y_S_win + Y_shift-5, 25, 25, no, 1);
              }          
          }
          
            myGLCD.setFont(SevenSegNumFont);                
            myGLCD.setColor(VGA_SILVER);  
            myGLCD.printNumI(WrMemo, 365, Mkk+9, 3, '0');  // выбранный параметр в окно редактирования
            myGLCD.setFont(BigFont);
            myGLCD.setFontAlt(BFontRu);

            WinRamka (355, Mkk, 113, 69, VGA_LIME, 0);
   
            Vklad_L_old = Vklad_L;
            Cln_st = false;
            
        }
        
       /*   if (TikTime() && Vklad_G == 3) {    // отображение времени во вкладке ОБЩИЕ
            if (Vklad_L!=0)  myGLCD.setColor(VGA_SILVER);
              else  myGLCD.setColor(VGA_LIME);
           // myGLCD.setFont(BigFontRus);
            sprintf (buf, "%02d:%02d:%02d\n", hh, mm, ss);            
            myGLCD.print(buf, 302,  Y_shift);   //Y_S_win +
          } */
      }
      break;
    case REFLOW_STATE_SET_EDIT:     {          //  редактирование параметра
#ifdef SetKalk
        if (updateScreen) {
          WinRamka (10, 105, 460, 203, VGA_BLACK, 1);
          WinRamka (10, 105, 460, 203, VGA_SILVER, 0);
      #if defined(Set_Picture) && defined(Set_Touch)
          myGLCD.drawBitmap(377, 267, 96, 50, Graf5, 1);
      #endif
          myGLCD.setColor(VGA_LIME);
         // myGLCD.setFont(BigFontRus);
         // myGLCD.print((char*) Ad_tekct, 20, 120);  // выводим текст названия параметра
          printFromPGM (&myStr3[Gi][Li], 20, 120);  // выводим текст названия параметра
          if (Vklad_G == 0 && Vklad_L == 2) Edit_Byte = *(int*)Wr_mem;
            else Edit_Byte = *(byte*)Wr_mem;
          Edit_Byte_old = Edit_Byte;
       j=0;  w=0;
          for (i = 0; i < 10; i++) {      // рисуем сенсорные кнопки
            if (i>=5) { j=Batt_Y+10; w=5;  }
            WinRamka (20+(i-w)*(Batt_X+10), 189+j, Batt_X, Batt_Y, VGA_SILVER, 0);
            myGLCD.setColor(VGA_LIME);
            myGLCD.printNumI(i, 42+(i-w)*(Batt_X+10), 207+j);   // цифры в кнопках
            }
          Edit_old = -1;
          K_Kpres_ok = false;
          
         updateScreen = false;          
        }
 #else
        if (updateScreen) {
          WinRamka (355, Mkk, 113, 69, VGA_RED, 0);
      #ifdef Set_Touch
            //WinRamka (355, 240, 113, 69, VGA_SILVER, 0);
        #ifdef Set_Picture
            myGLCD.drawBitmap(377, 267, 96, 50, Graf5, 1);
        #endif
      #endif
          if (Vklad_G == 0 && Vklad_L == 2) Edit_Byte = *(int*)Wr_mem;
            else Edit_Byte = *(byte*)Wr_mem;
          Edit_old = Edit_Byte;
          Edit_Byte_old = Edit_Byte;
          K_Kpres_ok = false;     
          updateScreen = false;
        }
 #endif        
        if (Edit_old != Edit_Byte) {
          myGLCD.setColor(VGA_ORAN);
          if (Edit_Byte_old == Edit_Byte) myGLCD.setColor(VGA_SILVER);
          myGLCD.setFont(SevenSegNumFont);
          myGLCD.printNumI(Edit_Byte, 365, Mkk+9 , 3, '0');
          myGLCD.setFont(BigFont);
          myGLCD.setFontAlt(BFontRu);

          Edit_old = Edit_Byte;
        }
      }
      break;
    case REFLOW_STATE_CLOCK_EDIT:   {          //  редактирование параметра
       if (updateScreen) {
        //Stat = 1;
        SetTimClock ();
        updateScreen = false;
        EnClSet = false;
        }
       ssR = ss;
       Pr_StelsR();
      }
      break;       
    case REFLOW_STATE_PROFILE:      {          //  просмотр профиля
        if (updateScreen) {
          myGLCD.clrScr();
          PrPrint(0, 2);
          updateScreen = false;
          K_Setka();
          K_Kpres_ok = false;
          In_Line(20);        // end  updateScreen
      #if defined(Set_Picture) && defined(Set_Touch)
          myGLCD.drawBitmap(377, 267, 96, 50, Graf5, 1);
      #endif

        }
      }
      break;
    case REFLOW_STATE_PROFILE_LOAD: {          //  загрузка профиля
        if (updateScreen) {
          WinRamka (10, 105, 460, 203, VGA_BLACK, 1);
          WinRamka (10, 105, 460, 203, VGA_RED, 0);
      #if defined(Set_Picture) && defined(Set_Touch)
          myGLCD.drawBitmap(377, 267, 96, 50, Graf5, 1);
      #endif
          myGLCD.setColor(VGA_LIME); 
          printFromPGM (&myStr3[Gi][Li], 10, Y_shift);  // выводим текст названия параметра
         // myGLCD.print(myStr3[Vklad_G][0], 10, Y_shift); 
          NewPos = ArObsi[1];
          #ifdef SetEncoder 
            encoder.setPosition(NewPos);
          #endif  
          LastPos = NewPos;
          K_Kpres_ok = false;
          Stat = 1;
          Obsi2_Old = 15;
          updateScreen = false;
          }
        if (Obsi2_Old != ArObsi[1]) {
          Obsi2_Old = ArObsi[1];

          myGLCD.setColor(VGA_BLACK);
          myGLCD.fillRoundRect(312, Y_shift-5, 337, Y_shift + 20);
          
          if (Stat == 2) myGLCD.setColor(VGA_RED); 
             else myGLCD.setColor(VGA_SILVER);
          printFromPGM (&myText[2], 440, Y_shift);                    // текст OK
          if (Stat == 1)  myGLCD.setColor(VGA_RED); 
             else myGLCD.setColor(VGA_SILVER);
          if (ArObsi[1] == 0)   printFromPGM (&myText[3], 300, Y_shift+1); // "ВСЕХ   "
            else {
              printFromPGM (&myText[4], 300, Y_shift+1);              // "ИЗ  "
              i = 0;
              if (ArObsi[1] == 10) i = 16;
              myGLCD.printNumI(ArObsi[1], 370+i, Y_shift, 2, ' ');    // номер выводимого профиля
             
              myGLCD.setColor(VGA_BLACK);
              myGLCD.fillRoundRect(15, 115 , 468, 131);
              myGLCD.setColor(VGA_ORAN);
              printFromPGM (&(AdrProfN[ArObsi[1]-1]), 15, 116);       // название выводимого профиля
              myGLCD.setColor(VGA_LIME);
              printFromPGM (&myText[5], 15, 148);                     // " НИЗ   1     2     3     4 ";
              myGLCD.setColor(VGA_SILVER);
              for (j=2; j<=4; j++) {                                  // столбец "НИЗ"
                if (j == 3) {
                  tmp = 256 * pgm_read_byte_near(ProfDate[ArObsi[1]-1]+j+1);
                  tmp = tmp + pgm_read_byte_near(ProfDate[ArObsi[1]-1]+j);
                } else  {
                  if (j == 4) {
                    tmp = pgm_read_byte_near(ProfDate[ArObsi[1]-1]+j+1);
                    } else tmp = pgm_read_byte_near(ProfDate[ArObsi[1]-1]+j);
                }
                if (j == 2) myGLCD.printNumF(tmp * 0.1, 0, 26, 185+(j-2)*33);
                  else myGLCD.printNumI(tmp, 26, 185+(j-2)*33, 3, ' ');
                }
              for (j=8; j<=19; j++) {                                 // столбцы по шагам
                i = (j)%4; int k = (j-8)/4;
                tmp = pgm_read_byte_near(ProfDate[ArObsi[1]-1]+j);
                if (j >=8 && j <= 11) myGLCD.printNumF(tmp * 0.1, 0, 108 + i*96, 185);
                   else myGLCD.printNumI(tmp, 108 + i*96, 185+k*33, 3, ' ');
                }
            }
          }
        }
      break;
    case REFLOW_STATE_BRAZE_START:  {          // Старт пайки все начальные установки
        myGLCD.clrScr();
        PrPrint(0, 2);
        updateScreen = false;
        K_Setka();
        HeavyStart = false; 
        if (HeavyBottom) { 
          if (tc2 < ArObsi[4]) {
            HeavyStart = true;  
            tc2 = ArObsi[4]; 
            }           
          }
        In_Line(tc2);
        //  фиксируем размер стола
        if (u.Profili.TableSize >= 1)   digitalWrite(P1_PIN, SetReleON);
        if (u.Profili.TableSize >= 2)   digitalWrite(P2_PIN, SetReleON);
        if (u.Profili.TableSize >= 3)   digitalWrite(P3_PIN, SetReleON);

     // digitalWrite(P4_PIN, HIGH);   

        tone(buzzerPin, 1045, 500);  //звуковой сигнал при старте профиля
        delay(200);
        ChangeState(REFLOW_STATE_BRAZE_NOW,0);
        TopStart = false;
        BottomStart = false; 
        HeavyText = false;
        FlTone = false;
        F_Alarm = false;
        Hstart = false;
        mm = 0; ss = 0;       // секундомер в ноль
        BrStartTime = millis();
        BotStartTime = millis();
        Count1 = 0; Count2 = 0; BrStep = 0; BrStepOld = 15; Smi = 0;
        BrTg = M_tg_Line(BrStep);
        //Serial.print("Tg - "); Serial.println(BrTg);
#ifdef SetInterrupt
        attachInterrupt(SetInterrupt, Dimming, RISING); // настроить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
       #if defined(__AVR__)
          MsTimer2::set(10, Dimming); // 100ms period
          MsTimer2::start();
       #elif defined(ESP8266) || defined(ESP32)  
          timerAlarmWrite(Timer0_Cfg, 100000, true); // 100ms period
          timerAlarmEnable(Timer0_Cfg);
       #endif  
#endif
        digitalWrite(buzzerPin, LOW);
        integra = 0;
        integra2 = 0;
        currentStep = 0;
        bottomMaxPwr = u.Profili.max_pwr_BOTTOM;
        DtimTop = u.Profili.dwellTimerBOTTOM;
      }
      break;
    case REFLOW_STATE_BRAZE_NOW:    {          // процесс пайки графики
        if (millis() > nextRead1)   {          // график температуры nextRead1
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;
          TempRead();    //  считываем температуру

          if (HeavyStart) {
            if (ArObsi[4] != 0 && Input2 <= ArObsi[4]) {     // запускаем преднагрев низа
              if (!HeavyText) {           // 
                HeavyText = true;
                myGLCD.setColor(VGA_LIME);
             //   myGLCD.setFont(BigFontRus);
                printFromPGM (&myText[6], 20, 302);   // text:ПРЕДВАРИТЕЛЬНЫЙ НАГРЕВ НИЗА
                bottomTemp = ArObsi[4];
                bottomMaxPwr = ArObsi[5]; 
                }
              }
            if (Input2 > ArObsi[4]) {     // если температура платы больше выходим из режима преднaгрева 
                HeavyStart = false;                
                bottomMaxPwr = u.Profili.max_pwr_BOTTOM; 
                tone(buzzerPin, 1105, 200);  //звуковой сигнал
                }
             TempBraze ();
             }
            else {     
              // начало основного профиля
              if (BrStep < BrStepMax+2) {            // если не конец профиля
                if (chast < 450) Count1++;
                chast = Count1 / 4;
                kluch =  Count1 % 4;
                if (BrStep < 2) {    
                  // включение Нижнего подогрева
                  if (!BottomStart) {             // вывод текста
                    BottomStart = true;
                    BrTgBot = M_tg_Line(BrStep);
                    myGLCD.setColor(VGA_LIME);
                    printFromPGM (&myText[7], 20, 302);   // text:НИЖНИЙ НАГРЕВАТЕЛЬ ВКЛЮЧЕН
                    }              
                  if (BottTime == 0) {
                    if (chast < Pr_Line_M[BrStep][TimeEnd_M]) {   // рост температуры
                        SetpointB2 = Pr_Line_M[BrStep][TempSt_M] + BrTgBot * Count1 / 4;
                        }  
                       else {                                     // удержание, переход к включению верха
                        SetpointB2 = Pr_Line_M[BrStep][TempEnd_M];                       
                        if (BrStepMax != 0) {  
                          BrStep +=2;    
                          }
                        }
                     bottomTemp = SetpointB2;
                     }
                   else {        // тут считаем температуру на опережение                    
                    if (chast < Pr_Line_M[BrStep][TimeEnd_M]) {   // рост температуры
                        SetpointB2 = Pr_Line_M[BrStep][TempSt_M] + BrTgBot * Count1 / 4;
                        } 
                    if (chast + BottTime < Pr_Line_M[BrStep][TimeEnd_M]) {   // рост температуры
                        SetpointB = Pr_Line_M[BrStep][TempSt_M] + BrTgBot * (Count1/4 + BottTime - Pr_Line_M[BrStep][TimeSt_M]);
                        }  
                       else {                                     // удержание, переход к включению верха
                        SetpointB = Pr_Line_M[BrStep][TempEnd_M];                       
                        if (BrStepMax != 0) {
                          BrStep +=2;                          
                          }
                       } 
                    bottomTemp = SetpointB; 
                  }
                  if (BrStepMax != 0) {   
                    if (ArObsi[2] != 0 && !TopStart && Input1 > ArObsi[2] && HeavyTop) {  // включение преднагрева ВЕРХА
                      if(!FlTone) {                 // выдаем сообщение 
                        FlTone = true; 
                        myGLCD.setColor(VGA_LIME);
                        printFromPGM (&myText[8], 20, 302);   // text:ПРЕДВАРИТЕЛЬНЫЙ НАГРЕВ ВЕРХА
                        tone(buzzerPin, 1105, 200);  //звуковой сигнал
                        }
                      Output1 = ArObsi[3];          // минимальная мощность
                      }
                    } 
                  }
                if (BrStepMax != 0) {
                  if (BrStepMax != 0 && !Hstart && chast >= Pr_Line_M[1][TimeSt_M]) {
                    Hstart= true;
                    }
                  if (Hstart)  Setpoint2 = GetTempBot(chast + DtimTop);
                
                  if (!TopStart && BrStep >= 2) {                   //  профиль не запущен
                    if (chast >= Pr_Line_M[BrStep][TimeSt_M] && BrStepMax >= 2) {   // пора ли включать ВЕРХ
                      TopStart = true;
                      myGLCD.setColor(VGA_LIME);                     
                      printFromPGM (&myText[9], 20, 302);     // text:ВЕРХНИЙ НАГРЕВАТЕЛЬ ВКЛЮЧЕН                      
                      BrTgTop = M_tg_Line(BrStep);
                      Count2 = 0;
                      currentStep = BrStep/2;
                      tone(buzzerPin, 1105, 200);  //звуковой сигнал
                      }
                    } 
                   else {                            //  профиль запущен                  
                    if (chast <= Pr_Line_M[BrStep][TimeEnd_M] ) {                         
                        Setpoint1 = Pr_Line_M[BrStep][TempSt_M] + BrTgTop * Count2 / 4; // рост температуры
                        Count2++;
                        }  
                    if (HeavyTop)  {               //  если верх инерционный  
                      topTemp = Setpoint2;
                      } else topTemp = Setpoint1;                  
                    if (chast > Pr_Line_M[BrStep][TimeEnd_M]) { // пора ли переходить на следующий шаг
                      BrStep++;
                      currentStep = BrStep/2;
                      BrTgTop = M_tg_Line(BrStep);
                      Count2 = 0;
                      tone(buzzerPin, 1105, 200);  //звуковой сигнал
                      }
                    }
                  }
                // вывод информации на экран и в монитор РС
                    if (kluch == 0) {      // выводим показания секундомера
                      Sec_metr();
                      myGLCD.printNumI(currentStep, 2, 302, 1);
                      if (Hstart) {             // рисуем ожидаемый график2 верха
                        myGLCD.setColor(VGA_YELLOW);
                        M_dr_point(chast + DtimTop, Setpoint2);   
                        M_dr_point(chast + DtimTop, Setpoint2+1); 
                        }
                      if (BottTime != 0) {      // рисуем ожидаемый график2 низа 
                        myGLCD.setColor(VGA_YELLOW);
                        M_dr_point(chast + BottTime, SetpointB);   
                        M_dr_point(chast + BottTime, SetpointB+1);
                        }
                    }
                    if (kluch == 1) {      // рисуем графики
                      // WinStartTime = micros();
                      TimeLine(chast + X_graf);             // линия времени
                      myGLCD.setColor(VGA_RED);
                      M_dr_point(chast - 2, SetpointB2);    // рисуем ожидаемый график низа
                      if (TopStart) {
                        myGLCD.setColor(VGA_ORAN);
                        M_dr_point(chast - 2, Setpoint1);                    
                      }                      
                      myGLCD.setColor(VGA_LIME);
                      M_dr_point (chast - 2, tc2);           // рисуем график низ
                      myGLCD.setColor(VGA_AQUA);
                      M_dr_point (chast - 2, tc1);           // рисуем график верх
                      TempBraze ();
                      //  Pr_WinTime();    // на экран засеченное время в мсек
                    }
                    if (kluch == 2) {      // выводим в порт температуру
                      myGLCD.setColor(VGA_SILVER);
                      myGLCD.print(F(":"), 432, TempY);
        #ifdef SetConnectPC
                      sprintf (buf, "OK%03d%03d%03d%03d%03d\r\n", int(Output1), int(Output2), tc1, tc2, int(profileName)); // график ПК
                      Serial.print(buf);
        #endif
                    }
                    if (kluch == 3) {      // работа защиты от отвала термопары 
                        if (ArObsi[0] == 1) {   // проверка защиты низа разрешена
                          if (Gvard_If()) {
                            F_Alarm = true;
                            ChangeState(REFLOW_STATE_BRAZE_STOP,1);   // завершение пайки
                            }
                        }
                      }
                                    
                    }  
                else  {                             // завершаем профиль
                    ChangeState(REFLOW_STATE_BRAZE_STOP,1);   // завершение пайки
                  }
              }
            if (millis() - BotStartTime < 3000) Output2 = 5; // первые 3 сек мощность низа =5%
              else  Output2 = Pid2(Input2, bottomTemp, u.Profili.kp2, u.Profili.ki2, u.Profili.kd2);
            if (TopStart) Output1 = Pid1(Input1, topTemp, u.Profili.kp1, u.Profili.ki1, u.Profili.kd1);
          
        }
      }
      break;
    case REFLOW_STATE_BRAZE_STOP:   {           // STOP процесса пайки
        if (updateScreen) {
          digitalWrite(P1_PIN, SetReleOFF);
          digitalWrite(P2_PIN, SetReleOFF);
          digitalWrite(P3_PIN, SetReleOFF);
          digitalWrite(P4_PIN, SetReleOFF);
          TopStart = false;
          Output2 = 0;
          Output1 = 0;

#ifdef SetInterrupt
          detachInterrupt(SetInterrupt); // остановить порт прерывания(0 или 1) 2й или 3й цифровой пин
#else
          #if defined(__AVR__)
            MsTimer2::stop();
          #elif defined(ESP8266) || defined(ESP32)
            timerAlarmDisable(Timer0_Cfg);
          #endif  
#endif
          digitalWrite(RelayPin1, LOW);
          digitalWrite(RelayPin2, LOW);

          if (F_Alarm) {
              myGLCD.setColor(VGA_RED);
            //  myGLCD.setFont(BigFontRus);
              printFromPGM (&myText[10], 20, 302);
              }
            else {
              myGLCD.setColor(VGA_LIME);
             // myGLCD.setFont(BigFontRus);
              printFromPGM (&myText[11], 5, 302);
              }


          tone(buzzerPin, 945, 500);  //звуковой сигнал
          delay(150);
          tone(buzzerPin, 645, 500);  //звуковой сигнал
          updateScreen = false;
        }
        if (millis() > nextRead1)     {          // график температуры nextRead1
          nextRead1 = millis() + SENSOR_SAMPLING_TIME;
          if (chast < 450) Count1++;
          chast = Count1 / 4;
          kluch =  Count1 % 4;
          TempRead();    //  считываем температуру
          if (kluch == 0) {
            myGLCD.setColor(VGA_LIME);
            M_dr_point (chast - 2, tc2);           // рисуем график низ
            myGLCD.setColor(VGA_AQUA);
            M_dr_point (chast - 2, tc1);           // рисуем график верх
            }
          TempBraze ();
        }
        break;
      }
  }
}  // end loop
//
