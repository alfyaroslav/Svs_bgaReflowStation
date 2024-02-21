// ------------ Профили ----------------------
#define numMax 10           // Максимальное количество профилей
#define Adres 1          // адрес начала записи в EPROM 
 #if defined(__AVR__)
    #define ArrMax 50            // Максимальное количество символов в названии профиля (в русских буквах в два раза меньше)
 #elif defined(ESP8266) || defined(ESP32)
    #define ArrMax 100
 #endif
bool stProf = false;
byte numProf;
struct Profili_t {         // основные поля профиля
  char HeadProf[ArrMax];   // заголовок профиля ArrMax символов
  byte TableSize;          // размер низа
  byte rampRateBOTTOM;     // скорсть нагрева низа
  #if defined(__AVR__)
  int temperatureBOTTOM;  // температура низа в градусах
  #elif defined(ESP8266) || defined(ESP32)
  long int temperatureBOTTOM;  // температура низа в градусах
  #endif
  byte dwellTimerBOTTOM;   // время в сек перехода к включению верха
  byte min_pwr_BOTTOM;     // мощность низа в % min
  byte max_pwr_BOTTOM;     //     --            max
  byte rampRateStep[4];    // скорсть нагрева верхом по шагам
  byte temperatureStep[4]; // температура верха по шагам
  byte dwellTimerStep[4];  // время в сек перехода на следующий шаг
  byte min_pwr_TOPStep[4]; // min мощности по шагам
  byte max_pwr_TOPStep[4]; // max мощности по шагам
  byte kp1;                // коэф ПИД 1 верха
  byte ki1;
  byte kd1;
  byte kp2;                // коэф ПИД 2 низа
  byte ki2;
  byte kd2;
};
union {
  byte Mode[sizeof(Profili_t)];
  Profili_t Profili;
} u;
int SizePrrof = sizeof(Profili_t);
// --------- profile end ------------------------------
byte Cgr, CTgr = 0;
int Xgr, XTgr = 2;                 // x координата графика
int er1 = 1, er2 = 1;
int reg1, reg2;
int pwr1, pwr2;
double prev_millis = 0;
boolean out1, out2, Hstart;
boolean TopStart = false, BottomStart = false, HeavyStart = false, HeavyText = false;
boolean FlTone = false, EnClSet = false;
String DuStr = "";
byte currentProfile, Smi=0, DtimTop;
byte currentStep, BrStep, BrStepOld;
byte profileName;
double counter;
long previousMillis;          // это для счетчиков
#if defined(__AVR__)
  int8_t buffer[ArrMax];          // 
#elif defined(ESP8266) || defined(ESP32)
  char buffer[ArrMax];          //
#endif 
// ----------------------------------------------------
#if defined(__AVR__)
 extern byte ProfDate[10][34];
 #elif defined(ESP8266) || defined(ESP32)
 extern byte ProfDate[10][38];
 #ifdef Enable_Bluetooth
 char buf2[32];   //буфер вывода сообщений через сом порт
 #endif
 #endif
// extern char* AdrProfN[10];
// -------секция ввода/вывода для ПЭВМ-----------------
char buf[20];   //буфер вывода сообщений через сом порт

typedef enum REFLOW_STATE {   // состояния контроллера
  REFLOW_STATE_IDLE,          // главный экран
  REFLOW_STATE_SETTING,       // меню настроек
  REFLOW_STATE_CLOCK_EDIT,    // установка часов экран 
  REFLOW_STATE_SET_EDIT,      // редактирование выбранной настройки
  REFLOW_STATE_PROFILE_LOAD,  // загрузка профилей в eeprom 
  REFLOW_STATE_PROFILE,       // просмотр профиля
  REFLOW_STATE_BRAZE_START,   // Старт пайки
  REFLOW_STATE_BRAZE_NOW,     // отработка профиля
  REFLOW_STATE_BRAZE_STOP    // Стоп пайки
}
reflowState_t;
reflowState_t reflowState;          // Reflow oven controller state machine state variable

#define SENSOR_SAMPLING_TIME 250    //read tc every second
#define i_min 0.0//минимум И составляющей
#define i_max 100.0//максимум И составляющей

unsigned long nextRead1; //переменная для обновления текущей температуры
unsigned long WinStartTime, BrStartTime, BotStartTime, TouchSet, TouchClock;
byte Setpoint1, Setpoint2, bottomMaxPwr, SetpointB, SetpointB2;
byte Output1, Output2, TouOld = 10;
int8_t Shag = 0, Shag_old = 0;

float Input_f1, Input_f2, Input_ft1, Input_ft2;
float integra, integra2, BrTg, BrTg2, BrTgBot, BrTgTop;
float e1, p1, d1, e2, p2, d2;
double Input1,  Setpoint1d, T_mlx;
double Input2,  Setpoint2d;
double bottomTemp, topTemp;
int SP1 = Setpoint1, SP2 = Setpoint2, Count1, Count2;
int tc1, tc2;                       // переменные для калмана
int i, j, w;
int chast, kluch;
int tmp, DisXSize, DisYSize;
byte ArObsi[6]; 
  // 0 - SetQvard включение защиты низа
  // 1 - 
  // 2 - температура старта преднагрева верха(если 0 то по профилю) 
  // 3 - мощность подаваемая на верх при преднагреве
  // 4 - температура старта профиля при инерционном низе (если 0 то профиль стартует сразу)
  // 5 - мощность подаваемая на низ при преднагреве

byte Obsi2_Old;

void *Adresa[4][6] = {              // адреса переменных для меню настроек
  {&u.Profili.TableSize, &u.Profili.rampRateBOTTOM, &u.Profili.temperatureBOTTOM, &u.Profili.dwellTimerBOTTOM, &u.Profili.min_pwr_BOTTOM, &u.Profili.max_pwr_BOTTOM },
  {&Shag, &u.Profili.rampRateStep[0], &u.Profili.temperatureStep[0], &u.Profili.dwellTimerStep[0], &u.Profili.min_pwr_TOPStep[0], &u.Profili.max_pwr_TOPStep[0]},
  {&u.Profili.kp1, &u.Profili.ki1, &u.Profili.kd1, &u.Profili.kp2, &u.Profili.ki2, &u.Profili.kd2},
  {&ArObsi[0], &ArObsi[1], &ArObsi[2], &ArObsi[3], &ArObsi[4], &ArObsi[5]}
};       
bool Cln_st = false;
boolean alarmOn = false;
boolean updateScreen = true;        //Update whole screen boolean
// --------------------
#define VGA_ORAN 0xFD40
#define Draw_X 90
#define Draw_Y 80
#define Simb_X 18*16
#define Win1 4                                // всего вкладок меню
#define Win2 6                                // кол-во строк
#define K_line 12
#define Py_pr 31 //40
#define Yset 25                               // отступ сверху                          
#define Ysize 36                              // высота окна меню
#define Ywin0 Ysize+Yset+6                    // начало окна параметров
#define Ywin1 Ysize+Yset
#define X_graf 27
#define Y_graf Py_pr+246
#define T_SetY 293
#define B_SetX 3
#define B_SetY 140
#define BattX 87          // размер кнопки по X 
#define BattY 60          // размер кнопки по Y
#define TempY 30
#define TimeSt_M 0
#define TempSt_M 1
#define TimeEnd_M 2
#define TempEnd_M 3
#define Batt_X 60         // размер сенсорных цифровых кнопок 
#define Batt_Y 50  
#define Mkk 109
#define KnLeft 0
#define KnRight 1
#define KnUp 2
#define KnDown 3
#define KnOk 4
#define KnClock 5
#define KnESC 6
#define KnEdit 7
#define KnEdUp 8
#define KnEdDown 9

int BattSet[10][4] = { {B_SetX, B_SetY + 10 + BattY, B_SetX + BattX, B_SetY + 10 + 2 * BattY},
  {B_SetX, B_SetY, B_SetX + BattX, B_SetY + BattY},
  {479 - B_SetX - BattX, B_SetY, 479 - B_SetX, B_SetY + BattY},
  {479 - B_SetX - BattX, B_SetY + 10 + BattY, 479 - B_SetX, B_SetY + 10 + 2 * BattY},
  {B_SetX, B_SetY + 20 + 2 * BattY, 479 - B_SetX, 319},
  {480/2-42, 320/2-25-41, 480/2+40, 320/2-25+40},     // часы 
  {0, 30, 40, 300},
  {355, Mkk, 468, Mkk+69},
  {425, 267, 479, 320},
  {377, 267, 424, 320}
};
byte  BrStepMax, Gi, Li;
int Edit_Byte_old, Edit_old, ByteMax;
int Xsize;                                    // ширина окна меню
int Y_S_win;                                  // высота строки
int Edit_Byte, Y_shift;
int8_t Vklad_G = 0, Vklad_G_old = 0, Vklad_G_Mem, Vklad_L_Mem;          // выбранная вкладка (новая, старая)
int8_t Vklad_L = 0, Vklad_L_old = 0;          // выбранная строка  (новая, старая)

bool F_Alarm, TouDec = false;
