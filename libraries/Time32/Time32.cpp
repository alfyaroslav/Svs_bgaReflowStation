/*
  Time32.c - low level time and date functions for ESP32 and Arduino
  Copyright (c) Rafael Reyes 2022
  Copyright (c) Michael Margolis 2009-2014

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  1.0  6  Jan 2010 - initial release
  1.1  12 Feb 2010 - fixed leap year calculation error
  1.2  1  Nov 2010 - fixed setTime bug (thanks to Korman for this)
  1.3  24 Mar 2012 - many edits by Paul Stoffregen: fixed timeStatus() to update
                     status, updated examples for Arduino 1.0, fixed ARM
                     compatibility issues, added TimeArduinoDue and TimeTeensy3
                     examples, add error checking and messages to RTC examples,
                     add examples to DS1307RTC library.
  1.4  5  Sep 2014 - compatibility with Arduino 1.5.7

  -------------------------------- Time32 ------------------------------------------------
  
  1.0  14 Jul 2022 - fixed "conflicting declaration 'typedef time_t'" on ESP32 enviroment. 
                   - added typedef time32_t to avoid conflict with newlib or other libs.
                   - added support fix 2106 problem. Tested until 31th December of 16383.
                   - added leap_seconds function to calc leap seconds. 
  1.0.1 15 Jul 2022 - fixed 'setTime' to use new time32_t.
                    - fixed return values of 'year'. 
  1.1  18 Jul 2022 - added 'Spanish' language support.
  1.1.1 5 Dec 2022 - fixed some spanish words.
  1.1.2 5 Apr 2023 - fixed leap_seconds function and data.
  1.1.3 13 Apr 2023 - fixed definition #define DAYS_PER_A_WEEK ((time32_t)(7UL)) to prevent
			conflict with NEOGPS library.
*/

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "TimeLib32.h"

static tmElements_t tm;      // a cache of time elements
static time32_t cacheTime;   // the time the cache was updated
static uint32_t syncInterval = 300;  // time sync will be attempted after this many seconds

void refreshCache(time32_t t) {
  if (t != cacheTime) {
    breakTime(t, tm); 
    cacheTime = t; 
  }
}

int hour() { // the hour now 
  return hour(now()); 
}

int hour(time32_t t) { // the hour for the given time
  refreshCache(t);
  return tm.Hour;  
}

int hourFormat12() { // the hour now in 12 hour format
  return hourFormat12(now()); 
}

int hourFormat12(time32_t t) { // the hour for the given time in 12 hour format
  refreshCache(t);
  if( tm.Hour == 0 )
    return 12; // 12 midnight
  else if( tm.Hour  > 12)
    return tm.Hour - 12 ;
  else
    return tm.Hour ;
}

uint8_t isAM() { // returns true if time now is AM
  return !isPM(now()); 
}

uint8_t isAM(time32_t t) { // returns true if given time is AM
  return !isPM(t);  
}

uint8_t isPM() { // returns true if PM
  return isPM(now()); 
}

uint8_t isPM(time32_t t) { // returns true if PM
  return (hour(t) >= 12); 
}

int minute() {
  return minute(now()); 
}

int minute(time32_t t) { // the minute for the given time
  refreshCache(t);
  return tm.Minute;  
}

int second() {
  return second(now()); 
}

int second(time32_t t) {  // the second for the given time
  refreshCache(t);
  return tm.Second;
}

int day(){
  return(day(now())); 
}

int day(time32_t t) { // the day for the given time (0-6)
  refreshCache(t);
  return tm.Day;
}

int weekday() {   // Sunday is day 1
  return  weekday(now()); 
}

int weekday(time32_t t) {
  refreshCache(t);
  return tm.Wday;
}

int month(){
  return month(now()); 
}

int month(time32_t t) {  // the month for the given time
  refreshCache(t);
  return tm.Month;
}

uint16_t year() {  // as in Processing, the full four digit year: (2009, 2010 etc) 
  return year(now()); 
}

uint16_t year(time32_t t) { // the year for the given time
  refreshCache(t);
  return tmYearToCalendar(tm.Year);
}

/*============================================================================*/	
/* functions to convert to and from system time */
/* These are for interfacing with time services and are not normally needed in a sketch */

// leap year calculator expects year argument as years offset from 1970
#define LEAP_YEAR(Y)     ( ((1970+(Y))>0) && !((1970+(Y))%4) && ( ((1970+(Y))%100) || !((1970+(Y))%400) ) )

static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

void breakTime(time32_t timeInput, tmElements_t &tm){
// break the given time32_t into time components
// this is a more compact version of the C library localtime function
// note that year is offset from 1970 !!!

  uint16_t year;
  uint8_t month, monthLength;
  unsigned long days;

  #ifdef USE_UINT64_T
  uint64_t time;
  time = (uint64_t)timeInput;
  #else
  uint32_t time;
  time = (uint32_t)timeInput;
  #endif

  tm.Second = time % 60;
  time /= 60; // now it is minutes
  tm.Minute = time % 60;
  time /= 60; // now it is hours
  tm.Hour = time % 24;
  time /= 24; // now it is days
  tm.Wday = ((time + 4) % 7) + 1;  // Sunday is day 1 
  
  year = 0;  
  days = 0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
  }
  tm.Year = year; // year is offset from 1970 
  
  days -= LEAP_YEAR(year) ? 366 : 365;
  time  -= days; // now it is days in this year, starting at 0
  
  days=0;
  month=0;
  monthLength=0;
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } else {
        monthLength=28;
      }
    } else {
      monthLength = monthDays[month];
    }
    
    if (time >= monthLength) {
      time -= monthLength;
    } else {
        break;
    }
  }
  tm.Month = month + 1;  // jan is month 1  
  tm.Day = time + 1;     // day of month
}

// Info from https://www.iana.org/time-zones Version 2023c (Released 2023-03-28) tzdb-2023c.tar.lz.
static const uint32_t leap_seconds_time_t[] = {
  (uint32_t)78796799,  // 1972 Jun 30 23:59:59 (+1)
  (uint32_t)94694399,  // 1972 Dec 31 23:59:59 (+1)
  (uint32_t)126230399, // 1973 Dec 31 23:59:59 (+1)
  (uint32_t)157766399, // 1974 Dec 31 23:59:59 (+1)
  (uint32_t)189302399, // 1975 Dec 31 23:59:59 (+1)
  (uint32_t)220924799, // 1976 Dec 31 23:59:59 (+1)
  (uint32_t)252460799, // 1977 Dec 31 23:59:59 (+1)
  (uint32_t)283996799, // 1978 Dec 31 23:59:59 (+1)
  (uint32_t)315532799, // 1979 Dec 31 23:59:59 (+1)
  (uint32_t)362793599, // 1981 Jun 30 23:59:59 (+1)
  (uint32_t)394329599, // 1982 Jun 30 23:59:59 (+1)
  (uint32_t)425865599, // 1983 Jun 30 23:59:59 (+1)
  (uint32_t)489023999, // 1985 Jun 30 23:59:59 (+1)
  (uint32_t)567993599, // 1987 Dec 31 23:59:59 (+1)
  (uint32_t)631151999, // 1989 Dec 31 23:59:59 (+1)
  (uint32_t)662687999, // 1990 Dec 31 23:59:59 (+1)
  (uint32_t)709948799, // 1992 Jun 30 23:59:59 (+1)
  (uint32_t)741484799, // 1993 Jun 30 23:59:59 (+1)
  (uint32_t)773020799, // 1994 Jun 30 23:59:59 (+1)
  (uint32_t)820454399, // 1995 Dec 31 23:59:59 (+1)
  (uint32_t)867715199, // 1997 Jun 30 23:59:59 (+1)
  (uint32_t)915148799, // 1998 Dec 31 23:59:59 (+1)
  (uint32_t)1136073599,// 2005 Dec 31 23:59:59 (+1)
  (uint32_t)1230767999,// 2008 Dec 31 23:59:59 (+1)
  (uint32_t)1341100799,// 2012 Jun 30 23:59:59 (+1)
  (uint32_t)1435708799,// 2015 Jun 30 23:59:59 (+1)
  (uint32_t)1483228799,// 2016 Dec 31 23:59:59 (+1)
  0xffffffff
};

unsigned int leap_seconds(time32_t time){
  unsigned int leap_secs = 0;

  (time > (time32_t)63072000) ? leap_secs = 10 : leap_secs = 0; // 1972 Jan 1 00:00:00 (+10) Star leap seconds.

  for(unsigned int i = 0; i < sizeof(leap_seconds_time_t)/sizeof(leap_seconds_time_t[0]); i++){
    if(time > leap_seconds_time_t[i]) leap_secs++;
  }

  return leap_secs;
}

time32_t makeTime(const tmElements_t &tm){   
// assemble time elements into time32_t 
// note year argument is offset from 1970 (see macros in time.h to convert to other formats)
// previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9
  
  int i;
  #ifdef USE_UINT64_T
  uint64_t seconds;
  #else
  uint32_t seconds;
  #endif

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds= tm.Year*(SECS_PER_DAY * 365);
  for (i = 0; i < tm.Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds += SECS_PER_DAY;   // add extra days for leap years
    }
  }
  
  // add days for this year, months start from 1
  for (i = 1; i < tm.Month; i++) {
    if ( (i == 2) && LEAP_YEAR(tm.Year)) { 
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds+= (tm.Day-1) * SECS_PER_DAY;
  seconds+= tm.Hour * SECS_PER_HOUR;
  seconds+= tm.Minute * SECS_PER_MIN;
  seconds+= tm.Second;

  return (time32_t)seconds; 
}
/*=====================================================*/	
/* Low level system time functions  */
#ifdef USE_UINT64_T
static uint64_t sysTime = 0;
static uint64_t prevMillis = 0;
static uint64_t nextSyncTime = 0;
#else
static uint32_t sysTime = 0;
static uint32_t prevMillis = 0;
static uint32_t nextSyncTime = 0;
#endif
static timeStatus_t Status = timeNotSet;

getExternalTime getTimePtr;  // pointer to external sync function
//setExternalTime setTimePtr; // not used in this version

#ifdef TIME_DRIFT_INFO   // define this to get drift data
time32_t sysUnsyncedTime = 0; // the time sysTime unadjusted by sync  
#endif


time32_t now() {
	// calculate number of seconds passed since last call to now()
  while (millis() - prevMillis >= 1000) {
		// millis() and prevMillis are both unsigned ints thus the subtraction will always be the absolute value of the difference
    sysTime++;
    prevMillis += 1000;	
#ifdef TIME_DRIFT_INFO
    sysUnsyncedTime++; // this can be compared to the synced time to measure long term drift     
#endif
  }
  if (nextSyncTime <= sysTime) {
    if (getTimePtr != 0) {
      time32_t t = (time32_t)getTimePtr();
      if (t != 0) {
        setTime(t);
      } else {
        nextSyncTime = sysTime + syncInterval;
        Status = (Status == timeNotSet) ?  timeNotSet : timeNeedsSync;
      }
    }
  }  
  return (time32_t)sysTime;
}

void setTime(time32_t t) { 
#ifdef TIME_DRIFT_INFO
 if(sysUnsyncedTime == 0) 
   sysUnsyncedTime = t;   // store the time of the first call to set a valid Time   
#endif
#ifdef USE_UINT64_T
  sysTime = (uint64_t)t;
#else
  sysTime = (uint32_t)t;
#endif
  nextSyncTime = sysTime + syncInterval;
  Status = timeSet;
  prevMillis = millis();  // restart counting from now (thanks to Korman for this fix)
} 

void setTime(int hr,int min,int sec,int dy, int mnth, int yr){
 // year can be given as full four digit year or two digts (2010 or 10 for 2010);  
 //it is converted to years since 1970
  if( yr > 99)
      yr = yr - 1970;
  else
      yr += 30;  
  tm.Year = yr;
  tm.Month = mnth;
  tm.Day = dy;
  tm.Hour = hr;
  tm.Minute = min;
  tm.Second = sec;
  setTime(makeTime(tm));
}

void adjustTime(long adjustment) {
  sysTime += adjustment;
}

// indicates if time has been set and recently synchronized
timeStatus_t timeStatus() {
  now(); // required to actually update the status
  return Status;
}

void setSyncProvider( getExternalTime getTimeFunction){
  getTimePtr = getTimeFunction;  
  nextSyncTime = sysTime;
  now(); // this will sync the clock
}

void setSyncInterval(time32_t interval){ // set the number of seconds between re-sync
  syncInterval = (uint32_t)interval;
  nextSyncTime = sysTime + syncInterval;
}
