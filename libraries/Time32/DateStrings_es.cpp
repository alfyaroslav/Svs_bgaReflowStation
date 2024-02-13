/* DateStrings_es.cpp
 * Definitions for date strings 'Spanish' language for use with the Time32 library
 *
 * Updated for Arduino 1.5.7 18 July 2014
 *
 * No memory is consumed in the sketch if your code does not call any of the string methods
 * You can change the text of the strings, make sure the short strings are each exactly 3 characters 
 * the long strings can be any length up to the constant dt_MAX_STRING_LEN defined in TimeLib.h
 * 
 */

#include <Arduino.h>

// Arduino.h should properly define PROGMEM, PGM_P, strcpy_P, pgm_read_byte, pgm_read_ptr
// But not all platforms define these as they should.  If you find a platform needing these
// defined, or if any this becomes unnecessary as platforms improve, please send a pull req.
#if defined(ESP8266)
#undef PROGMEM
#define PROGMEM
#endif

#include "TimeLib32.h"

 
// the short strings for each day or month must be exactly dt_SHORT_STR_LEN_ES
#define dt_SHORT_STR_LEN_ES  3 // the length of short strings

static char buffer_es[dt_MAX_STRING_LEN_ES+1];  // must be big enough for longest string and the terminating null

const char monthStr0_es[] PROGMEM = "";
const char monthStr1_es[] PROGMEM = "Enero";
const char monthStr2_es[] PROGMEM = "Febrero";
const char monthStr3_es[] PROGMEM = "Marzo";
const char monthStr4_es[] PROGMEM = "Abril";
const char monthStr5_es[] PROGMEM = "Mayo";
const char monthStr6_es[] PROGMEM = "Junio";
const char monthStr7_es[] PROGMEM = "Julio";
const char monthStr8_es[] PROGMEM = "Agosto";
const char monthStr9_es[] PROGMEM = "Septiembre";
const char monthStr10_es[] PROGMEM = "Octubre";
const char monthStr11_es[] PROGMEM = "Noviembre";
const char monthStr12_es[] PROGMEM = "Diciembre";

const PROGMEM char * const PROGMEM monthNames_P_es[] =
{
    monthStr0_es,monthStr1_es,monthStr2_es,monthStr3_es,monthStr4_es,monthStr5_es,monthStr6_es,
    monthStr7_es,monthStr8_es,monthStr9_es,monthStr10_es,monthStr11_es,monthStr12_es
};

const char monthShortNames_P_es[] PROGMEM = "ErrEneFebMarAbrMayJunJulAgoSepOctNovDic";

const char dayStr0_es[] PROGMEM = "Err";
const char dayStr1_es[] PROGMEM = "Domingo";
const char dayStr2_es[] PROGMEM = "Lunes";
const char dayStr3_es[] PROGMEM = "Martes";
const char dayStr4_es[] PROGMEM = "Miércoles";
const char dayStr5_es[] PROGMEM = "Jueves";
const char dayStr6_es[] PROGMEM = "Viernes";
const char dayStr7_es[] PROGMEM = "Sábado";

const PROGMEM char * const PROGMEM dayNames_P_es[] =
{
   dayStr0_es,dayStr1_es,dayStr2_es,dayStr3_es,dayStr4_es,dayStr5_es,dayStr6_es,dayStr7_es
};

const char dayShortNames_P_Es[] PROGMEM = "ErrDomLunMarMieJueVieSab";

/* functions to return date strings */

char* monthStr_es(uint8_t month)
{
    strcpy_P(buffer_es, (PGM_P)pgm_read_ptr(&(monthNames_P_es[month])));
    return buffer_es;
}

char* monthShortStr_es(uint8_t month)
{
   for (int i=0; i < dt_SHORT_STR_LEN_ES; i++)      
      buffer_es[i] = pgm_read_byte(&(monthShortNames_P_es[i+ (month*dt_SHORT_STR_LEN_ES)]));  
   buffer_es[dt_SHORT_STR_LEN_ES] = 0;
   return buffer_es;
}

char* dayStr_es(uint8_t day) 
{
   strcpy_P(buffer_es, (PGM_P)pgm_read_ptr(&(dayNames_P_es[day])));
   return buffer_es;
}

char* dayShortStr_es(uint8_t day) 
{
   uint8_t index = day*dt_SHORT_STR_LEN_ES;
   for (int i=0; i < dt_SHORT_STR_LEN_ES; i++)      
      buffer_es[i] = pgm_read_byte(&(dayShortNames_P_Es[index + i]));  
   buffer_es[dt_SHORT_STR_LEN_ES] = 0; 
   return buffer_es;
}
