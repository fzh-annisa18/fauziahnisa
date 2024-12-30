#include "variabel.h"
void ambilWaktu(){
   DateTime now = rtc.now();
  sprintf(timeString, "%02d/%02d/%04d %02d:%02d:%02d",
          now.day(), now.month(), now.year(),
          now.hour(), now.minute(), now.second());
}