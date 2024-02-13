/*
 * ESP32.ino
 * example code illustrating Time library on ESP32 boards.
 *
 * This example need Sunrise and Timezone32 libraries. See on my GitHub:
 * https://github.com/RafaelReyesCarmona
 */

#include <Arduino.h>

#define USE_UINT64_T 1 // Use define to fix 2106 year problem. Only for ESP enviroments.

#define YEAR 2130   // Define the year to serial print sunrise, sunset and noon.

#include <Sunrise.h>
#include <TimeLib32.h>
#include <Timezone32.h>

// create a Sunrise object
Sunrise mySunrise(37.88533, -4.78043);       //Córdoba, Spain.
//Sunrise mySunrise(82.67255, -24.63867);   //"America/Godthab",
//Sunrise mySunrise(-22.48549, 134.41406); //"Australia/Darwin"

TimeElements mytime;
time32_t timenow;
/*
TimeChangeRule Darwin = {"ACST", Last, Sun, Mar, 1, 570};
Timezone myTimezone(Darwin);
/*
TimeChangeRule UST = {"U-2", Last, Sat, Mar, 22, -120}; //"America/Godthab",
TimeChangeRule UT = {"U-3", Last, Sat, Oct, 23, -180}; //"America/Godthab",
Timezone myTimezone(UST,UT);
*/
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       // Central European Standard Time
Timezone CE(CEST, CET);
#define myTimezone CE

void setup(){
  Serial.begin(9600);
  mySunrise.Actual(); //Actual, Civil, Nautical, Astronomical

  byte h,m,s;
  int t;
  for(int mo=1;mo<13;mo++){
  for(int d=1;d<30;d+=5){
  Serial.printf("%d-%d-",d,mo,);
  Serial.println(YEAR);
  Serial.println("Sunrise Precise hour:");
  mytime.Day = d;
  mytime.Month = mo;
  mytime.Year = YEAR - 1970;
  timenow = makeTime(mytime);
  // t= minutes past midnight of sunrise (6 am would be 360)
  t=mySunrise.SolarTime(timenow); // (month,day) - january=1
  if(t>=0){
    h=hour(myTimezone.toLocal(mySunrise.RiseTime()));
    m=minute(myTimezone.toLocal(mySunrise.RiseTime()));
    s=second(myTimezone.toLocal(mySunrise.RiseTime()));
    Serial.print("The sun rises at ");
    Serial.print(h, DEC);
    Serial.print(":");
    if(m<10) Serial.print("0");
    Serial.print(m,DEC);
    Serial.print(":");
    if(s<10) Serial.print("0");
    Serial.println(s,DEC);

    h=hour(myTimezone.toLocal(mySunrise.SetTime()));
    m=minute(myTimezone.toLocal(mySunrise.SetTime()));
    s=second(myTimezone.toLocal(mySunrise.SetTime()));
    Serial.print("The sun sets at ");
    Serial.print(h, DEC);
    Serial.print(":");
    if(m<10) Serial.print("0");
    Serial.print(m,DEC);
    Serial.print(":");
    if(s<10) Serial.print("0");
    Serial.println(s,DEC);

    h=hour(myTimezone.toLocal(mySunrise.NoonTime()));
    m=minute(myTimezone.toLocal(mySunrise.NoonTime()));
    s=second(myTimezone.toLocal(mySunrise.NoonTime()));
    Serial.print("Noon at ");
    Serial.print(h, DEC);
    Serial.print(":");
    if(m<10) Serial.print("0");
    Serial.print(m,DEC);
    Serial.print(":");
    if(s<10) Serial.print("0");
    Serial.print(s,DEC);
    Serial.print("   T:");
    Serial.println(t, DEC);
  }else{ // 
    Serial.println("There are either penguins or polar bears around here!");
  }
  Serial.println("----------------------------------");
  delay(10);
  }
  }
Serial.println("-----------------END-----------------");
}

void loop(){
}
