#define CLK 5
#define DIO 4
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
#define BTN_PIN 3  
int timerForStop =  10000 ;
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
unsigned long timer3;
bool wasPresed = false;
int buf;
int i;
int k;
void setup() {
  pinMode(10, INPUT_PULLUP);
  pinMOde(3, OUTPUT);
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
 static int b;
  if (IsFirstTouch && butt1.state()) {
  // mySerial.println(Deteckter());
  a = Deteckter();
  b = Distance();
  mySerial.print(Time());
  mySerial.print("|");
  mySerial.print(a );
  mySerial.print("|");
  mySerial.print( b);
  mySerial.print("|");
  mySerial.println("5234");
  print(a);
  delay(100);
    IsFirstTouch = false;
    
  }
 if (millis() - timer3 >= timerForStop) { 
    timer3 = millis(); // сброс
  print(0);
 
  mySerial.print(Time());
  mySerial.print("|");
  mySerial.print(0 );
  mySerial.print("|");
  mySerial.print( b);
  mySerial.print("|");
  mySerial.println("5234");
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
  if(buf > 25){
    tone(3,1000);
    }
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



String Time(){
 uint32_t sec = millis() / 1000ul;      // полное количество секунд
  int timeHours = (sec / 3600ul);        // часы
  int timeMins = (sec % 3600ul) / 60ul;  // минуты
  int timeSecs = (sec % 3600ul) % 60ul;  // секунды


  return  String(timeHours) + ":" + String(timeMins) + ":" + String(timeSecs) ;
}
