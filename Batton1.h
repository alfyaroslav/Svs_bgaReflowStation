 //--------настройка кнопок управления------------------------------------

#ifdef SetDigitBatton
  #define Batt_UP A11
  #define Batt_DWN A12
  #define Batt_LFT A13
  #define Batt_RHT A14
  #define Batt_MID A15
  Cl_do_btn_long Btn_UP(Batt_UP);
  Cl_do_btn_long Btn_DWN(Batt_DWN);
  Cl_do_btn_long Btn_LFT(Batt_LFT);
  Cl_do_btn_long Btn_RHT(Batt_RHT);
  Cl_do_btn_long Btn_MID(Batt_MID);
  // --------------------------------------------
  void longPr_MID () {
    return;
  }
#endif

  boolean T_KeyUp_Old = false, T_KeyDown_Old = false;
  boolean T_KeyNext = false, T_KeyOk = false, T_KeyClock = false;
  boolean T_KeyLeft_Old = false, T_KeyRight_Old = false;
  boolean K_Kpres_ok = false, K_Lpres_ok = false;

  #define Debion 10

byte StTouch;
bool btn = 1, oldBtn;
bool bounce = 0;            // антидребезговый флаг
bool button_state = 0;
uint32_t time_Pressed = 0;
uint32_t last_state = 0 ;
#define StShot 1
#define StLong 2
 
