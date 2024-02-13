// Подгружаем шрифты
#if defined(__AVR__)
 extern uint8_t SmallFont[];
 extern uint8_t BigFont[];
 extern uint8_t BFontRu[];
 // extern uint8_t BigFontRus[];       //Кирилица
 extern uint8_t SevenSegNumFont[];
#endif  

// ---- картинка на стартовый экран
#ifdef SetPicHeater
#if defined(__AVR__)
  extern unsigned int Heater2[0x1000];
#elif defined(ESP8266) || defined(ESP32)
 extern unsigned short Heater2[0x1000];
#endif  
#endif
// ---- Иконки
#ifdef Set_Picture
#if defined(__AVR__)
  extern unsigned int Graf[0xCC0];
  extern unsigned int Graf2[0xCC0];
  extern unsigned int Graf3[0xCC0];
  extern unsigned int Graf4[0xCC0];
  extern unsigned int Graf5[0x12C0];
  extern unsigned int yes[0x271];
  extern unsigned int no[0x271];
#elif defined(ESP8266) || defined(ESP32)
  extern unsigned short Graf[0xCC0];
  extern unsigned short Graf2[0xCC0];
  extern unsigned short Graf3[0xCC0];
  extern unsigned short Graf4[0xCC0];
  extern unsigned short Graf5[0x12C0];
  extern unsigned short yes[0x271];
  extern unsigned short no[0x271];
#endif

#endif
