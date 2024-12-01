#define CLK 5
#define DIO 4
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
#define BTN_PIN 3  

#include "GyverButton.h"
GButton butt1(BTN_PIN);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 9); 

#include <EEPROM.h>
const float d = 0.66;
bool isActive = false;
int speed;
const float minSpeed = 2;
const float maxSpeed = 40;
float minTime = 0;
float maxTime = 0;
double t;
float V;
float S;
bool IsFirstTouch=true;
bool isFirstDetect;
bool isDetect;
bool IsDetectSpeed = false;
int distance = 0;
unsigned long timer;
unsigned long timer1;
unsigned long timer2;
bool wasPresed = false;
int buf;
int i;
int k;
void setup() {
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
  disp.clear();
  disp.brightness(7);
  S = PI * d;
  Serial.println(S);
  EEPROM.get(100, distance);
  minTime = S / (maxSpeed / 3.6f);
  Serial.println(minTime);
  maxTime = S / (minSpeed / 3.6f);
  Serial.println(maxTime);
}

void loop() {
 butt1.tick();
 static int a;
  if (IsFirstTouch && butt1.state()) {
  // mySerial.println(Deteckter());
  a = Deteckter();
  mySerial.print("10:30:20");
  mySerial.print("|");
  mySerial.print(a );
  mySerial.print("|");
  mySerial.print( Distance());
  mySerial.print("|");
  mySerial.println("5234");
  print(a);
    IsFirstTouch = false;
  }

  if (IsFirstTouch == false  && butt1.state()==false) {
     IsFirstTouch = true;
  }
 
}



int Deteckter() {
  timer1 = millis();
  t = (timer1 - timer) / 1000.0f;
 timer = millis();
  float V = S / t;
 
   speed = V * 3.6;
  buf = speed;
  return speed;
}

int Distance() {
  distance += S;
  EEPROM.put(100, distance);
  return distance;
}

void print(int print) {
  disp.clear();
  disp.displayInt(print);
}


