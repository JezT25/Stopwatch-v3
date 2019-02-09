#include "module.h"

void setup() {
  pinMode(A, OUTPUT);  //Ten Hour
  pinMode(B, OUTPUT);  //Hour
  pinMode(C, OUTPUT);  //Ten Minute
  pinMode(D, OUTPUT);  //Minute
  pinMode(E, OUTPUT);  //Tens
  pinMode(Fe, OUTPUT);  //Ones
  pinMode(AA, OUTPUT);  //A
  pinMode(BB, OUTPUT);  //B
  pinMode(CC, OUTPUT);  //C
  pinMode(DD, OUTPUT);  //D
  pinMode(ClrA, OUTPUT); //Clear First Segment
  pinMode(ClrB, OUTPUT); //Clear Second Segment
  pinMode(ClrC, OUTPUT); //Clear Third Segment
  pinMode(Buzzer, OUTPUT); //Buzzer
  pinMode(Butt1, INPUT_PULLUP); //Upper Button
  pinMode(Butt2, INPUT_PULLUP); //Lower Button
  pinMode(cMode, INPUT_PULLUP); //Change Mode Button
  pinMode(LPM, INPUT); //Display Sensor
  pinMode(BPM, INPUT); //Battery Sensor
}

void loop() {
  //TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME////TIME//
  onehour = hour % 10;
  tenhour = hour / 10;

  unsigned long currentMillis = millis();
  unsigned long cmilli = micros();

  if (currentMillis - previousMillis > interval - 3.33333) {
    previousMillis = currentMillis;
    onesec++;
    if (onesec == 10) {
      tensec++;
      onesec = 0;
    }
    if (tensec == 6) {
      onemin++;
      tensec = 0;
      if (analogRead(A5) <= 750 && analogRead(LPM) > 100) {
        toney(30);
        delay(100);
        toney(30);
        delay(100);
        toney(30);
      }
    }
    if (onemin == 10) {
      tenmin++;
      onemin = 0;
    }
    if (tenmin == 6) {
      hour++;
      tenmin = 0;
    }
    if (hour == 13) {
      hour = 1;
      tenmin = 0;
      onemin = 0;
      tensec = 0;
      onesec = 0;
    }
    if (relay == 1) {
      toney(300);
      relay1--;
      if (relay1 < 0) {
        displayDigit(Fe, 0);
        x = ones;
        y = tens;
        z = hundred;
        xx = thousand - 1;
        ones = -1;
        tens = 0;
        hundred = 0;
        thousand = 0;
        thou = 0;
        tenthou = 0;
        relay = 0;
        seconds = 10 * y + x;
        if (seconds <= 3) {
          seconds = seconds + 60;
        }
        mode = timermode;
        digitalWrite(Buzzer, 1);
      }
    }
    if (mode == timermode) {
      ones++; 
      if (seconds >= 60 && secondsbeep >= seconds - 4 && hundred == z - 1 && secondsbeep < seconds - 1 && xx > 0) {
        toney(100);
      }
      else if (seconds >= 62 && secondsbeep >= seconds - 62 && hundred == z && secondsbeep < seconds - 61 && xx > 0) {
        toney(100);
      }
      else if (seconds == 63 && secondsbeep >= seconds - 63 && hundred == z && secondsbeep < seconds - 62 && xx > 0) {
        toney(100);
      }
      else if (secondsbeep >= seconds - 4 && hundred == z && secondsbeep < seconds - 1 && xx > 0) {
        toney(100);
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (analogRead(LPM) < 100) {
    pb1mode();
    pb3mode();
    digitalWrite(A, 0);
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    digitalWrite(E, 0);
    digitalWrite(Fe, 0);
    digitalWrite(AA, 0);
    digitalWrite(BB, 0);
    digitalWrite(CC, 0);
    digitalWrite(DD, 0);
    digitalWrite(ClrA, 0);
    digitalWrite(ClrB, 0);
    digitalWrite(ClrC, 0);
    digitalWrite(Buzzer, 0);
  }
  else {
    //MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES////MODES//
    ///CLOCK MODE//////CLOCK MODE//////CLOCK MODE//////CLOCK MODE//////CLOCK MODE//////CLOCK MODE//////CLOCK MODE//////CLOCK MODE///
    if (mode == clockmode) {
      pb2clockmode();
      pb3mode();

      displayDigit(Fe, onesec);
      displayDigit(E, tensec);
      displayDigit(D, onemin);
      displayDigit(C, tenmin);
      displayDigit(B, onehour);
      displayDigit(A, tenhour);

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///CLOCK ADJUST//////CLOCK ADJUST//////CLOCK ADJUST//////CLOCK ADJUST//////CLOCK ADJUST//////CLOCK ADJUST//////CLOCK ADJUST///
    while (mode == clockadjust) {
      pb1clockadjust(segs);
      segs = pb2clockadjust(segs);

      onehour = hour % 10;
      tenhour = hour / 10;

      ledblink(250, segs);

      displayDigit(Fe, onesec);
      displayDigit(E, tensec);
      displayDigit(D, onemin);
      displayDigit(C, tenmin);
      displayDigit(B, onehour);
      displayDigit(A, tenhour);
    }
    ///TIMER MENU///TIMER MENU//////TIMER MENU///TIMER MENU//////TIMER MENU///TIMER MENU//////TIMER MENU///TIMER MENU//////TIMER MENU///
    if (mode == timermenu) {
      pb1timermenu();
      pb2timermenu();
      pb3mode();

      thou = thousand % 10;
      tenthou = thousand / 10;

      displayDigit(Fe, ones);
      displayDigit(E, tens);
      displayDigit(D, hundred);
      displayDigit(C, 11);
      displayDigit(B, thou);
      displayDigit(A, tenthou);

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///TIMER ADJUST//////TIMER ADJUST//////TIMER ADJUST//////TIMER ADJUST//////TIMER ADJUST//////TIMER ADJUST//////TIMER ADJUST///
    if (mode == timeradjust) {
      segs = pb1timeradjust(segs);
      segs = pb2timeradjust(segs);

      thou = thousand % 10;
      tenthou = thousand / 10;

      ledblink(250, segs);

      displayDigit(Fe, ones);
      displayDigit(E, tens);
      displayDigit(D, hundred);
      displayDigit(C, 11);
      displayDigit(B, thou);
      displayDigit(A, tenthou);
    }
    //TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE/////TIMER MODE///
    if (mode == timermode) {
      pb1timermode();
      pb2timermode();

      thou = xx % 10;
      tenthou = xx / 10;
      secondsbeep = 10 * tens + ones;

      //     if(ones==3 && tens==0 && hundred==0){  ///// NEXT PERSON INTERVAL
      //        tone(Buzzer, 3000, 1000);
      //       }

      if (ones == 1) {
        digitalWrite(Buzzer, 0);
      }
      if (ones == 10) {
        tens++;
        ones = 0;
      }
      if (tens == 6) {
        hundred++;
        tens = 0;
      }
      if (ones == x && tens == y && hundred == z && xx != 0) {
        xx--;
        thou = xx % 10;
        tenthou = xx / 10;
        displayDigit(Fe, 0);
        displayDigit(E, 0);
        displayDigit(D, 0);
        displayDigit(B, thou);
        displayDigit(A, tenthou);
        toney(1000);
        ones = 0;
        tens = 0;
        hundred = 0;
      }
      if (ones == x && tens == y && hundred == z && xx == 0) {
        mode = timermenu;
        displayDigit(Fe, 0);
        displayDigit(E, 0);
        displayDigit(D, 0);
        displayDigit(C, 11);
        displayDigit(B, 0);
        displayDigit(A, 0);
        toney(3000);
        ones = 0;
        tens = 0;
        hundred = 0;
        xx = 0;
      }

      displayDigit(Fe, ones);
      displayDigit(E, tens);
      displayDigit(D, hundred);
      displayDigit(C, 11);
      displayDigit(B, thou);
      displayDigit(A, tenthou);

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///COUNTER MODE//////COUNTER MODE//////COUNTER MODE//////COUNTER MODE//////COUNTER MODE//////COUNTER MODE//////COUNTER MODE//////COUNTER MODE///
    if (mode == countermode) {
      pb1countermode();
      pb2countermode();
      pb3mode();

      if (thousand == 0) {
        displayDigit(Fe, milli2);
        displayDigit(E, milli1);
        displayDigit(D, ones);
        displayDigit(C, tens);
        displayDigit(B, hundred);
        displayDigit(A, tenhun);
      }
      if (thousand > 0) {
        displayDigit(Fe, ones);
        displayDigit(E, tens);
        displayDigit(D, hundred);
        displayDigit(C, tenhun);
        displayDigit(B, tenthou);
        displayDigit(A, thou);
      }

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///COUNTER START//////COUNTER START//////COUNTER START//////COUNTER START//////COUNTER START//////COUNTER START//////COUNTER START//////COUNTER START///
    if (mode == counterstart) {

      pb1counterstart();
      pb2counterstart();

      if (cmilli - pmilli >= 1000000 - 3333.33) {
        pmilli = cmilli;
        ones++;
        if (ones == 10) {
          tens++;
          ones = 0;
        }
        if (tens == 6) {
          hundred++;
          tens = 0;
        }
        if (hundred == 10) {
          tenhun++;
          hundred = 0;
        }
        if (tenhun == 6) {
          thousand++;
          tenhun = 0;
        }
        if (thousand == 100) {
          ones = 0;
          tens = 0;
          hundred = 0;
          tenhun = 0;
          thousand = 0;
          milli1 = 0;
          milli2 = 0;
          mode = countermode;
        }
      }

      milli1 = (cmilli - pmilli) % 1000000 / 100000;
      milli2 = (cmilli - pmilli) % 100000 / 10000;
      tenthou = thousand % 10;
      thou = thousand / 10;

      if (thousand == 0) {
        displayDigit(Fe, milli2);
        displayDigit(E, milli1);
        displayDigit(D, ones);
        displayDigit(C, tens);
        displayDigit(B, hundred);
        displayDigit(A, tenhun);
      }
      if (thousand > 0) {
        displayDigit(Fe, ones);
        displayDigit(E, tens);
        displayDigit(D, hundred);
        displayDigit(C, tenhun);
        displayDigit(B, tenthou);
        displayDigit(A, thou);
      }

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE//////SPLIT MODE///
    if (mode == splitmode) {
      pb1splitmode();
      pb2splitmode();

      ledblinkz(300);

      if (cmilli - pmilli >= 1000000 - 3333.33) {
        pmilli = cmilli;
        cc++;
        if (cc == 10) {
          dd++;
          cc = 0;
        }
        if (dd == 6) {
          ee++;
          dd = 0;
        }
        if (ee == 10) {
          ff++;
          ee = 0;
        }
        if (ff == 6) {
          gg++;
          ff = 0;
        }
        if (gg == 100) {
          cc = 0;
          dd = 0;
          ee = 0;
          ff = 0;
          gg = 0;
          aa = 0;
          bb = 0;
          mode = countermode;
        }
      }

      bb = ((cmilli - pmilli) % 1000000 / 100000);
      aa = ((cmilli - pmilli) % 100000 / 10000);
      hh = gg % 10;
      ii = gg / 10;

      if (thousand == 0) {
        displayDigit(Fe, milli2);
        displayDigit(E, milli1);
        displayDigit(D, ones);
        displayDigit(C, tens);
        displayDigit(B, hundred);
        displayDigit(A, tenhun);
      }
      if (thousand > 0) {
        displayDigit(Fe, ones);
        displayDigit(E, tens);
        displayDigit(D, hundred);
        displayDigit(C, tenhun);
        displayDigit(B, tenthou);
        displayDigit(A, thou);
      }
    }
    ///SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE//////SPLIT DONE///
    if (mode == splitdone) {
      pb1splitdone();
      pb2splitdone();

      if (thousand == 0) {
        displayDigit(Fe, milli2);
        displayDigit(E, milli1);
        displayDigit(D, ones);
        displayDigit(C, tens);
        displayDigit(B, hundred);
        displayDigit(A, tenhun);
      }
      if (thousand > 0) {
        displayDigit(Fe, ones);
        displayDigit(E, tens);
        displayDigit(D, hundred);
        displayDigit(C, tenhun);
        displayDigit(B, tenthou);
        displayDigit(A, thou);
      }

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL//////SPLIT RECALL///
    if (mode == splitrecall) {
      pb1splitrecall();
      pb2splitrecall();

      hh = gg % 10;
      ii = gg / 10;

      if (thousand == 0) {
        displayDigit(Fe, smill1);
        displayDigit(E, smill2);
        displayDigit(D, cc);
        displayDigit(C, dd);
        displayDigit(B, ee);
        displayDigit(A, ff);
      }
      if (thousand > 0) {
        displayDigit(Fe, cc);
        displayDigit(E, dd);
        displayDigit(D, ee);
        displayDigit(C, ff);
        displayDigit(B, hh);
        displayDigit(A, ii);
      }

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
    ///RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY//////RELAY///
    if (mode == none) {
      displayDigit(Fe, relay1);
      displayDigit(E, 0);
      displayDigit(D, 0);
      displayDigit(C, 0);
      displayDigit(B, 0);
      displayDigit(A, 0);

      digitalWrite(8, 0);
      digitalWrite(9, 0);
      digitalWrite(10, 0);
    }
  }
}
