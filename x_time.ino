
//#include <Time.h> //http://www.arduino.cc/playground/Code/Time
//#include <TimeLib.h> // https://github.com/PaulStoffregen/Time

#include <Timezone.h>    //https://github.com/JChristensen/Timezone

// Central European Time Zone (Vienna)
TimeChangeRule myDST = {"CEDT", Last, Sun, Mar, 2, 120};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"CET", Last, Sun, Oct, 3,  60};     //Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);

TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
