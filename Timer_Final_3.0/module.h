///DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES//////DEFINED VARIABLES///
#define clockmode 0
#define clockadjust 1
#define timermode 2
#define timeradjust 3
#define timermenu 10
#define countermode 4
#define counterstart 5
#define splitmode 6
#define splitdone 7
#define splitrecall 8
#define none 9

#define Buzzer 13
#define LPM A1
#define AA A2
#define BB A3
#define CC A4
#define BPM A5
#define DD 0
#define A 7
#define B 6
#define C 5
#define D 4
#define E 3
#define Fe 2
#define ClrA 8
#define ClrB 9
#define ClrC 10
#define Butt1 11
#define Butt2 12
#define cMode 1

long previousMillis = 0;
long interval = 1000;

long pmilli = 0;

int seconds, secondsbeep;

int onesec, tensec, onemin, tenmin, hour = 12, onehour, tenhour;
int ones, tens, hundred, tenhun, thousand, thou, tenthou, tententhou, milli1, milli2;
int aa, bb, cc, dd, ee, ff, gg, hh, ii, smill1, smill2;
int x, y, z, xx;

int relay, relay1;

int mode = timermenu;

int segs;

int current1;
long millis_held1;
long secs_held1;
long prev_secs_held1;
byte previous1 = HIGH;
unsigned long firstTime1;

int current2;
long millis_held2;
long secs_held2;
long prev_secs_held2;
byte previous2 = HIGH;
unsigned long firstTime2;

int current3;
long millis_held3;
long secs_held3;
long prev_secs_held3;
byte previous3 = HIGH;
unsigned long firstTime3;

void toney(int del) {
  digitalWrite(Buzzer, 1);
  delay(del);
  digitalWrite(Buzzer, 0);
}

void displayDigit(int section, int digit) {
  if ((mode == clockmode || mode == clockadjust || mode == timermode || mode == counterstart || mode == splitmode || mode == splitdone || mode == splitrecall) && digit == 0 && section == A) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 1);
    digitalWrite(CC, 1);
    digitalWrite(DD, 1);
  }
  else if (digit <= 0) {
    digitalWrite(AA, 0);
    digitalWrite(BB, 0);
    digitalWrite(CC, 0);
    digitalWrite(DD, 0);
  }
  else if (digit == 1) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 0);
    digitalWrite(CC, 0);
    digitalWrite(DD, 0);
  }
  else if (digit == 2) {
    digitalWrite(AA, 0);
    digitalWrite(BB, 1);
    digitalWrite(CC, 0);
    digitalWrite(DD, 0);
  }
  else if (digit == 3) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 1);
    digitalWrite(CC, 0);
    digitalWrite(DD, 0);
  }
  else if (digit == 4) {
    digitalWrite(AA, 0);
    digitalWrite(BB, 0);
    digitalWrite(CC, 1);
    digitalWrite(DD, 0);
  }
  else if (digit == 5) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 0);
    digitalWrite(CC, 1);
    digitalWrite(DD, 0);
  }
  else if (digit == 6) {
    digitalWrite(AA, 0);
    digitalWrite(BB, 1);
    digitalWrite(CC, 1);
    digitalWrite(DD, 0);
  }
  else if (digit == 7) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 1);
    digitalWrite(CC, 1);
    digitalWrite(DD, 0);
  }
  else if (digit == 8) {
    digitalWrite(AA, 0);
    digitalWrite(BB, 0);
    digitalWrite(CC, 0);
    digitalWrite(DD, 1);
  }
  else if (digit == 9) {
    digitalWrite(AA, 1);
    digitalWrite(BB, 0);
    digitalWrite(CC, 0);
    digitalWrite(DD, 1);
  }
  else {
    digitalWrite(AA, 1);
    digitalWrite(BB, 1);
    digitalWrite(CC, 1);
    digitalWrite(DD, 1);
  }

  digitalWrite(section, 1);
  digitalWrite(section, 0);

  digitalWrite(AA, 0);
  digitalWrite(BB, 0);
  digitalWrite(CC, 0);
  digitalWrite(DD, 0);
}

///LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK///
void ledblink(unsigned int lengthms, int pinnum) {
  unsigned long currentMillis = millis();

  if (pinnum > 0) {
    if (currentMillis - previousMillis > lengthms) {
      previousMillis = currentMillis;

      digitalWrite(pinnum, !digitalRead(pinnum));
    }
  }
}
///LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK//////LED BLINK///
void ledblinkz(unsigned int lengthms) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > lengthms) {
    previousMillis = currentMillis;

    digitalWrite(8, !digitalRead(8));
    digitalWrite(9, !digitalRead(9));
    digitalWrite(10, !digitalRead(10));
  }
}
///BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS//////BUTTON COMMANDS///
void pb1mode() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        if (mode == timermenu) {
          ones = 0;
          tens = 0;
          hundred = 0;
          thousand = 0;
          thou = 0;
          tenthou = 0;
          milli1 = 0;
          milli2 = 0;
          aa = 0;
          bb = 0;
          cc = 0;
          dd = 0;
          ee = 0;
          ff = 0;
          gg = 0;
          hh = 0;
          ii = 0;
          smill1 = 0;
          smill2 = 0;
          mode = countermode;
        }
        else if (mode == countermode) {
          mode = clockmode;
          segs = 9;
        }
        else {
          mode = timermenu;
          ones = 0;
          tens = 0;
          hundred = 0;
          thousand = 0;
          thou = 0;
          tenthou = 0;
        }
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}

void pb3mode() {
  current3 = digitalRead(cMode);
  if (current3 == LOW && previous3 == HIGH && (millis() - firstTime3) > 200) {
    firstTime3 = millis();
  }
  millis_held3 = (millis() - firstTime3);
  secs_held3 = millis_held3 / 1000;
  if (millis_held3 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current3 == HIGH && previous3 == LOW) {
      if (secs_held3 <= 1.5) {
        toney(30);
        delay(100);
        toney(30);
        if (mode == timermenu) {
          ones = 0;
          tens = 0;
          hundred = 0;
          thousand = 0;
          thou = 0;
          tenthou = 0;
          milli1 = 0;
          milli2 = 0;
          aa = 0;
          bb = 0;
          cc = 0;
          dd = 0;
          ee = 0;
          ff = 0;
          gg = 0;
          hh = 0;
          ii = 0;
          smill1 = 0;
          smill2 = 0;
          mode = countermode;
        }
        else if (mode == countermode) {
          mode = clockmode;
          segs = 9;
        }
        else {
          mode = timermenu;
          ones = 0;
          tens = 0;
          hundred = 0;
          thousand = 0;
          thou = 0;
          tenthou = 0;
        }
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous3 = current3;
  prev_secs_held3 = secs_held3;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb2clockmode() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current2 == LOW && secs_held2 > prev_secs_held2) {                                              //PUSH BUTTON CLOCK MODE BUTTON 2
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 >= 2.5) {
        toney(300);
        mode = clockadjust;
        onesec = 0;
        tensec = 0;
        segs = 9;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1clockadjust(int segs) {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON CLOCK ADJUST BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        if (segs == 8) {
          hour++;
          if (hour == 13) {
            hour = 1;
          }
        }
        else if (segs == 9) {
          onemin++;
          if (onemin == 10) {
            tenmin++;
            onemin = 0;
          }
          if (tenmin == 6) {
            tenmin = 0;
            onemin = 0;
          }
        }
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
int pb2clockadjust(int segs) {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current2 == LOW && secs_held2 > prev_secs_held2) {                                            //PUSH BUTTON CLOCK ADJUST BUTTON 2
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
      segs = 0;
    }
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(50);
        if (segs == 9) {
          segs = 8;
          digitalWrite(9, 0);
        }
        else if (segs == 8) {
          segs = 9;
          digitalWrite(8, 0);
        }
      }
      if (secs_held2 == 1 || secs_held2 == 2 || secs_held2 > 3) {
        segs = 9;
      }
      if (secs_held2 >= 2.5) {
        toney(300);
        mode = clockmode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
  return segs;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1timermenu() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        if ((ones == 0 && tens > 0 && hundred == 0 && thousand > 0) || (ones == 0 && tens == 0 && hundred > 0 && thousand > 0) || (ones > 0 && tens > 0 && hundred > 0 && thousand > 0) || (ones > 0 && tens == 0 && hundred > 0 && thousand > 0) || (ones == 0 && tens >= 0 && hundred > 0 && thousand > 0) || (ones > 0 && tens > 0 && hundred == 0 && thousand > 0)) {
          relay = 1;
          relay1 = 3;
          mode = none;
        }
        else {
          toney(30);
          delay(100);
          toney(30);
          delay(100);
          toney(30);
        }
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2timermenu() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current2 == LOW && secs_held2 > prev_secs_held2) {
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 >= 2.5) {
        toney(300);
        x = 0;
        y = 0;
        z = 0;
        xx = 0;
        ones = 0;
        tens = 0;
        hundred = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
        segs = 10;
        mode = timeradjust;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pb1timeradjust(int segs) {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    if (current1 == LOW && secs_held1 > prev_secs_held1) {                                            //PUSH BUTTON TIMER ADJUST BUTTON 1
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
      segs = 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        if (segs == 8) {
          thousand++;
          if (thousand == 100) {
            thousand = 0;
          }
        }
        else if (segs == 10) {
          ones++;
          if (ones == 10) {
            tens++;
            ones = 0;
          }
          if (tens == 6) {
            tens = 0;
            ones = 0;
          }
        }
        else if (segs == 9) {
          hundred++;
          if (hundred == 10) {
            hundred = 0;
          }
        }
      }
      if (secs_held1 == 1 || secs_held1 == 2 || secs_held1 > 3) {
        segs = 10;
      }
      if (secs_held1 >= 2.5) {
        toney(150);
        thousand = 0;
        ones = 0;
        tens = 0;
        hundred = 0;
        segs = 10;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
  return segs;
}
int pb2timeradjust(int segs) {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON TIMER ADJUST BUTTON 2
    if (current2 == LOW && secs_held2 > prev_secs_held2) {
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
      segs = 0;
    }
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(50);
        if (segs == 8) {
          segs = 10;
          digitalWrite(8, 0);
        }
        else if (segs == 9) {
          segs = 8;
          digitalWrite(9, 0);
        }
        else if (segs == 10) {
          segs = 9;
          digitalWrite(10, 0);
        }
      }
      if (secs_held2 == 1 || secs_held2 == 2 || secs_held2 > 3) {
        segs = 10;
      }
      if (secs_held2 >= 2.5) {
        toney(300);
        mode = timermenu;
        digitalWrite(8, 0);
        digitalWrite(9, 0);
        digitalWrite(10, 0);
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
  return segs;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1timermode() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON TIMER MODE BUTTON 1
    if (current1 == LOW && secs_held1 > prev_secs_held1) {
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 >= 2.5) {
        toney(300);
        mode = timeradjust;
        x = 0;
        y = 0;
        z = 0;
        xx = 0;
        ones = 0;
        tens = 0;
        hundred = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2timermode() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON TIMER MODE BUTTON 2
    if (current2 == LOW && secs_held2 > prev_secs_held2) {
      digitalWrite(8, 1);
      digitalWrite(9, 1);
      digitalWrite(10, 1);
      delay(50);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 >= 2.5) {
        toney(300);
        mode = timeradjust;
        x = 0;
        y = 0;
        z = 0;
        xx = 0;
        ones = 0;
        tens = 0;
        hundred = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1countermode() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON COUNTER MODE BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        mode = counterstart;
        if (milli1 < 5) {
          ones--;
        }
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2countermode() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON COUNTER MODE BUTTON 2
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(150);
        ones = 0;
        tens = 0;
        hundred = 0;
        tenhun = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
        milli1 = 0;
        milli2 = 0;
        aa = 0;
        bb = 0;
        cc = 0;
        dd = 0;
        ee = 0;
        ff = 0;
        gg = 0;
        hh = 0;
        ii = 0;
        smill1 = 0;
        smill2 = 0;
        mode = countermode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1counterstart() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON COUNTER START BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        mode = countermode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2counterstart() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON COUNTER START BUTTON 2
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(50);
        cc = ones;
        dd = tens;
        ee = hundred;
        ff = tenhun;
        gg = thousand;
        mode = splitmode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1splitmode() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON SPLIT MODE BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        mode = splitdone;
        smill1 = aa;
        smill2 = bb;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2splitmode() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////// //PUSH BUTTON SPLIT MODE BUTTON 2
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(50);
        ones = cc;
        tens = dd;
        hundred = ee;
        tenhun = ff;
        thousand = gg;
        mode = counterstart;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1splitdone() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////// //PUSH BUTTON SPLIT DONE BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        mode = splitmode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2splitdone() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////// //PUSH BUTTON SPLIT DONE BUTTON 2
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(50);
        mode = splitrecall;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pb1splitrecall() {
  current1 = digitalRead(Butt1);
  if (current1 == LOW && previous1 == HIGH && (millis() - firstTime1) > 200) {
    firstTime1 = millis();
  }
  millis_held1 = (millis() - firstTime1);
  secs_held1 = millis_held1 / 1000;
  if (millis_held1 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON SPLIT RECALL BUTTON 1
    if (current1 == HIGH && previous1 == LOW) {
      if (secs_held1 <= 0) {
        toney(50);
        ones = cc;
        tens = dd;
        hundred = ee;
        tenhun = ff;
        thousand = gg;
        mode = counterstart;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous1 = current1;
  prev_secs_held1 = secs_held1;
}
void pb2splitrecall() {
  current2 = digitalRead(Butt2);
  if (current2 == LOW && previous2 == HIGH && (millis() - firstTime2) > 200) {
    firstTime2 = millis();
  }
  millis_held2 = (millis() - firstTime2);
  secs_held2 = millis_held2 / 1000;
  if (millis_held2 > 50) {
    ///////////////////////////////////////////////////////////////////////////////////////////////////PUSH BUTTON SPLIT RECALL BUTTON 2
    if (current2 == HIGH && previous2 == LOW) {
      if (secs_held2 <= 0) {
        toney(150);
        ones = 0;
        tens = 0;
        hundred = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
        milli1 = 0;
        milli2 = 0;
        aa = 0;
        bb = 0;
        cc = 0;
        dd = 0;
        ee = 0;
        ff = 0;
        gg = 0;
        hh = 0;
        ii = 0;
        smill1 = 0;
        smill2 = 0;
        mode = countermode;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////
  }
  previous2 = current2;
  prev_secs_held2 = secs_held2;
}

