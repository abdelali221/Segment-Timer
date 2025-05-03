#include <Wire.h>
#include <TM1650.h>
#include <ArduinoVT.h>

TM1650 d;
Term Term;

char time[] = {'0', '0', '0', '0', '\0'};
int sec;

void setup() {
  Wire.begin();
  d.init();
  Serial.begin(9600);
  Term.Clear();
  Term.SetCursPos(20, 1);
  Serial.print("Arduino SEG Clock \nMade By Abdelali221");
  if (d.displayRunning("    ArduIno SEg CLocH    ")) {
    while (d.displayRunningShift()) delay(200);
  }
  timesetup();  
}

void loop() {
  delay(500);
  d.setDot(1,true);
  delay(500);
  d.setDot(1,false);
  clockcounter();
  d.displayString(time);
}

void clockcounter() {

  if (sec < 60){
    sec++;
  }

  if (sec == 60) {
    sec = 0;
    time[3]++;
  }

  if (time[3] == 58) {
    time[3] = 48;
    time[2]++;
  }

  if (time[2] == 54) {
    time[1]++;
    time[2] = 48;
  }
  
  if (time[1] == 58) {
    time[1] = 48;
    time[0]++;
  }

  if (time[0] == 50 && time[1] == 52) {
    time[0] = 48;
    time[1] = 48;
  }
}

void timesetup() {
  bool exitloop = false;
  int c = 0;
  Term.Clear();
  Term.Return();
  Serial.println("Please Enter the Current Time");
  Serial.print("Hrs : ");
  while (!exitloop) {
    if (Serial.available()) {

      char chr = Serial.read();

      if ((chr == 10 || chr == 13 ) && c != 0) {
        if (c == 1) {
          time[1] = time[0];
          time[0] = 48;
        }
        exitloop = true;
      } else {
        if (chr >= '0' && chr <= '9') {
          if (c < 2) {
            time[c] = chr;
            Serial.print(chr);
            c++;
          }
        }
      }
    }
  }

  exitloop = false;
  c = 0;
  Term.Return();
  Serial.print("Mins : ");
  while (!exitloop) {
    if (Serial.available()) {

      char chr = Serial.read();

      if ((chr == 10 || chr == 13 ) && c != 0) {
        if (c == 1) {
          time[3] = time[2];
          time[2] = 48;
        }
        exitloop = true;
      } else {
        if (chr >= '0' && chr <= '9') {
          if (c < 2) {
            time[c + 2] = chr;
            Serial.print(chr);
            c++;
          }
        }
      }
    }
  }
}