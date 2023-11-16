
#define CLK 5
#define DIO 4
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
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
bool IsFirstTouch;
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
  isDetect = !digitalRead(2);
  if (sensor()) {
    i = Distance();
    k = Deteckter();
    print(i);
  }

  if (CheckButton()) {
    ChangeActive();
  }
  if (isActive) {
    print(k);
  }
}

bool sensor() {
  if (isDetect == true && isFirstDetect == false) {
    isFirstDetect = true;
    return true;
  }
  if (isDetect == false && isFirstDetect == true) {
    isFirstDetect = false;
  }
  return false;
}

int Deteckter() {
  timer1 = millis();
  t = (timer1 - timer) / 1000.0f;
  if (t < minTime) {
    speed = buf;
    return speed;
  }
  if (t > maxTime) {
    speed = 0;
    return speed;
  }
  float V = S / t;
  IsFirstTouch = false;
  speed = V * 3.6;
  buf = speed;
  return speed;
}

int Distance() {
  distance += S;
  EEPROM.put(100, distance);
  return distance;
}

bool CheckButton() {
  if (digitalRead(10) && wasPresed == false) {
    delay(20);
    Serial.println("button pressed");
    wasPresed = true;
  }
  if (!digitalRead(10) && wasPresed == true) {
    delay(20);
    Serial.println("button released");
    wasPresed = false;
    return true;
  }
  return false;
}
void print(int print) {
  disp.clear();
  disp.displayInt(print);
}

void ChangeActive() {
  isActive = !isActive;
}

void Timer() {
  if (millis() - timer2 > 10000) {
    timer2 = millis();
    IsDetectSpeed = false;
    return false;
  }
  return true;
}