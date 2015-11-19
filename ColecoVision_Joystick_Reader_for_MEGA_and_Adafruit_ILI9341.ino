#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

#define IN_PIN_1 22 //Brown UP
#define IN_PIN_2 24 //Red DOWN
#define IN_PIN_3 26 //Orange LEFT
#define IN_PIN_4 28 //Yellow RIGHT
#define IN_PIN_5 30 //Green
#define IN_PIN_6 32 //Blue BUTTON
#define IN_PIN_7 34 //Purple
#define IN_PIN_8 36 //Grey
#define IN_PIN_9 38 //White

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
uint8_t rotation=1;
int h, w, x, y, xk, yk = 0;
bool k1,k2,k3,k4,k5,k6,k7,k8,k9,k0,ka,kp = false;
bool ok1,ok2,ok3,ok4,ok5,ok6,ok7,ok8,ok9,ok0,oka,okp = false;
int mode = 2;

void setup() 
{
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(rotation);
  tft.fillScreen(ILI9341_BLACK);
  h = tft.height();  w = tft.width();
  Serial.print("H:"); Serial.println(h);
  Serial.print("W:");Serial.println(w);
  y = 60;
  x = w/2 - 60;
  xk = w/2 + 40;
  yk = y-25;

  if (mode == 1)
  {
    InitializeController_Coleco();
    DrawUI("Original Coleco", "n/c");
  }
  else if (mode == 2)
  {
    InitializeController_Coleco_Flashback();
    DrawUI("Coleco Flashback", "n/c");
  }

}

void loop()
{
  if (mode == 1)
  {
    ReadJoystick_Coleco();
    ReadKeypad_Coleco();
  }
  else if (mode == 2)
  {
    ReadJoystick_Coleco_Flashback();
    ReadButtons_Coleco_Flashback();
    ReadKeypad_Coleco_Flashback();
  }
}

void outputPinStateToSerial()
{  
  Serial.print("1:");Serial.println(digitalRead(IN_PIN_1));
  Serial.print("2:");Serial.println(digitalRead(IN_PIN_2)); 
  Serial.print("3:");Serial.println(digitalRead(IN_PIN_3)); 
  Serial.print("4:");Serial.println(digitalRead(IN_PIN_4)); 
  Serial.print("5:");Serial.println(digitalRead(IN_PIN_5));
  Serial.print("6:");Serial.println(digitalRead(IN_PIN_6)); 
  Serial.print("7:");Serial.println(digitalRead(IN_PIN_7)); 
  Serial.print("8:");Serial.println(digitalRead(IN_PIN_8)); 
  Serial.print("9:");Serial.println(digitalRead(IN_PIN_9));  
  Serial.println("====");
}

void InitializeController_Coleco_Flashback()
{
  pinMode (IN_PIN_1, INPUT_PULLUP); // + pin2 low = RB
  pinMode (IN_PIN_2, INPUT_PULLUP); //up
  //pinMode (IN_PIN_3, INPUT_PULLUP); // common always LOW?
  pinMode (IN_PIN_4, INPUT_PULLUP); 
  pinMode (IN_PIN_5, INPUT_PULLUP); //down
  pinMode (IN_PIN_6, INPUT_PULLUP); //left
  pinMode (IN_PIN_7, INPUT_PULLUP); //right
  pinMode (IN_PIN_8, INPUT_PULLUP); // + pin2 low = LB
  pinMode (IN_PIN_9, INPUT_PULLUP); 

  pinMode (IN_PIN_3, OUTPUT); digitalWrite(IN_PIN_3, LOW); //Common
}

void InitializeController_Coleco()
{
  pinMode (IN_PIN_1, INPUT_PULLUP); //Brown UP
  pinMode (IN_PIN_2, INPUT_PULLUP); //Red DOWN
  pinMode (IN_PIN_3, INPUT_PULLUP); //Orange LEFT
  pinMode (IN_PIN_4, INPUT_PULLUP); //Yellow RIGHT
  pinMode (IN_PIN_6, INPUT_PULLUP); //Blue BUTTON

  //Ground is switch between Pins 5 and 8 to mux Joystick with Keypad
  // JOYSTICK = Pin 5 GREEN HIGH && Pin 8 GRAY LOW
  // KEYPAD = Pin 5 GREEN LOW && Pin 8 GRAY HIGH
  pinMode (IN_PIN_5, OUTPUT);
  pinMode (IN_PIN_8, OUTPUT);
}

void ReadJoystick_Coleco_Flashback()
{
    if (digitalRead(IN_PIN_2) == LOW) drawUp(ILI9341_GREEN); else drawUp(ILI9341_BLACK);
    if (digitalRead(IN_PIN_5) == LOW) drawDown(ILI9341_GREEN); else drawDown(ILI9341_BLACK);
    if (digitalRead(IN_PIN_6) == LOW) drawLeft(ILI9341_GREEN); else drawLeft(ILI9341_BLACK);
    if (digitalRead(IN_PIN_7) == LOW) drawRight(ILI9341_GREEN); else drawRight(ILI9341_BLACK);

    Serial.println("=JOY=");
    outputPinStateToSerial();
}

void ReadButtons_Coleco_Flashback()
{
  pinMode (IN_PIN_2, OUTPUT); digitalWrite(IN_PIN_2, LOW);
  if (digitalRead(IN_PIN_1) == LOW) drawButton(-1,ILI9341_GREEN); else drawButton(-1,ILI9341_BLACK);
  if (digitalRead(IN_PIN_8) == LOW) drawButton(1,ILI9341_GREEN); else drawButton(1,ILI9341_BLACK);

  //Serial.println("=BUTTONS=");
  //outputPinStateToSerial();
  digitalWrite(IN_PIN_2, HIGH); pinMode (IN_PIN_2, INPUT_PULLUP);
}

void ReadKeypad_Coleco_Flashback()
{
  digitalWrite(IN_PIN_3, HIGH);
  pinMode (IN_PIN_9, OUTPUT); digitalWrite(IN_PIN_9, LOW); // k1 = pin5, k2 = 6, k3 = 7
  k1 = digitalRead(IN_PIN_5) == LOW;
  k2 = digitalRead(IN_PIN_6) == LOW;
  k3 = digitalRead(IN_PIN_7) == LOW;
  //if (digitalRead(IN_PIN_5) == LOW) drawKey (0,0,'1',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,0,'1',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_6) == LOW) drawKey (0,1,'2',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,1,'2',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_7) == LOW) drawKey (0,2,'3',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,2,'3',ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("=ROW1=");
  outputPinStateToSerial();
  digitalWrite(IN_PIN_9, HIGH); pinMode (IN_PIN_9, INPUT_PULLUP); 

  pinMode (IN_PIN_4, OUTPUT); digitalWrite(IN_PIN_4, LOW); //k4 = pin5, k5 = 6, k6 = 7
  k4 = digitalRead(IN_PIN_5) == LOW;
  k5 = digitalRead(IN_PIN_6) == LOW;
  k6 = digitalRead(IN_PIN_7) == LOW;
  //if (digitalRead(IN_PIN_5) == LOW) drawKey (1,0,'4',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,0,'4',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_6) == LOW) drawKey (1,1,'5',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,1,'5',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_7) == LOW) drawKey (1,2,'6',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,2,'6',ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("=ROW2=");
  outputPinStateToSerial();
  digitalWrite(IN_PIN_4, HIGH); pinMode (IN_PIN_4, INPUT_PULLUP); 
  
  pinMode (IN_PIN_8, OUTPUT); digitalWrite(IN_PIN_8, LOW); // k7 = pin5, k8 = 6, k9 = 7
  k7 = digitalRead(IN_PIN_5) == LOW;
  k8 = digitalRead(IN_PIN_6) == LOW;
  k9 = digitalRead(IN_PIN_7) == LOW;
  //if (digitalRead(IN_PIN_5) == LOW) drawKey (2,0,'7',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,0,'7',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_6) == LOW) drawKey (2,1,'8',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,1,'8',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_7) == LOW) drawKey (2,2,'9',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,2,'9',ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("=ROW3=");
  outputPinStateToSerial();
  digitalWrite(IN_PIN_8, HIGH); pinMode (IN_PIN_8, INPUT_PULLUP); 
   
  pinMode (IN_PIN_1, OUTPUT); digitalWrite(IN_PIN_1, LOW); // ka = pin5, k0 = 6, kp = 7
  ka = digitalRead(IN_PIN_5) == LOW;
  k0 = digitalRead(IN_PIN_6) == LOW;
  kp = digitalRead(IN_PIN_7) == LOW;
  //if (digitalRead(IN_PIN_5) == LOW) drawKey (3,0,'*',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,0,'*',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_6) == LOW) drawKey (3,1,'0',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,1,'0',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_7) == LOW) drawKey (3,2,'#',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,2,'#',ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("=ROW4=");
  outputPinStateToSerial();
  digitalWrite(IN_PIN_1, HIGH); pinMode (IN_PIN_1, INPUT_PULLUP); 

  drawKeyPress();
  digitalWrite(IN_PIN_3, LOW);
}

void ReadJoystick_Coleco()
{
  digitalWrite(IN_PIN_5, HIGH); digitalWrite(IN_PIN_8, LOW); //Set Mode to READ JOYSTICK

    if (digitalRead(IN_PIN_1) == LOW) drawUp(ILI9341_GREEN); else drawUp(ILI9341_BLACK);
    if (digitalRead(IN_PIN_2) == LOW) drawDown(ILI9341_GREEN); else drawDown(ILI9341_BLACK);
    if (digitalRead(IN_PIN_3) == LOW) drawLeft(ILI9341_GREEN); else drawLeft(ILI9341_BLACK);
    if (digitalRead(IN_PIN_4) == LOW) drawRight(ILI9341_GREEN); else drawRight(ILI9341_BLACK);
    if (digitalRead(IN_PIN_6) == LOW) drawButton(-1,ILI9341_GREEN); else drawButton(-1,ILI9341_BLACK);
}

void ReadKeypad_Coleco()
{
  digitalWrite(IN_PIN_5, LOW); digitalWrite(IN_PIN_8, HIGH); //Set Mode to READ KEYPAD

  bool p1 = digitalRead(IN_PIN_1);
  bool p2 = digitalRead(IN_PIN_2);
  bool p3 = digitalRead(IN_PIN_3);
  bool p4 = digitalRead(IN_PIN_4);
  //bool p6 = digitalRead(IN_PIN_6);

  k1 = ( p1 &&  p2 &&  p3 && !p4);
  k2 = ( p1 &&  p2 && !p3 &&  p4);
  k3 = (!p1 &&  p2 &&  p3 && !p4);
  k4 = (!p1 && !p2 && !p3 &&  p4);
  k5 = ( p1 && !p2 && !p3 &&  p4);
  k6 = (!p1 &&  p2 &&  p3 &&  p4);
  k7 = ( p1 &&  p2 && !p3 && !p4);
  k8 = ( p1 && !p2 && !p3 && !p4);
  k9 = ( p1 && !p2 &&  p3 &&  p4);
  ka = ( p1 && !p2 &&  p3 && !p4);
  k0 = (!p1 && !p2 &&  p3 &&  p4);
  kp = (!p1 &&  p2 && !p3 &&  p4);

  drawKeyPress();

//  if (k1 != ok1)
//  {
//    if (k1) drawKey (0,0,'1',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,0,'1',ILI9341_WHITE, ILI9341_BLACK);
//    ok1 = k1;
//  }
//  if (k2 != ok2)
//  {
//    if (k2) drawKey (0,1,'2',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,1,'2',ILI9341_WHITE, ILI9341_BLACK);
//    ok2 = k2;
//  }
//  if (k3 != ok3)
//  {
//    if (k3) drawKey (0,2,'3',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,2,'3',ILI9341_WHITE, ILI9341_BLACK);
//    ok3 = k3;
//  }
//  if (k4 != ok4)
//  {
//    if (k4) drawKey (1,0,'4',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,0,'4',ILI9341_WHITE, ILI9341_BLACK);
//    ok4 = k4;
//  } 
//  if (k5 != ok5)
//  {
//    if (k5) drawKey (1,1,'5',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,1,'5',ILI9341_WHITE, ILI9341_BLACK);
//    ok5 = k5;
//  } 
//  if (k6 != ok6)
//  {
//    if (k6) drawKey (1,2,'6',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,2,'6',ILI9341_WHITE, ILI9341_BLACK);
//    ok6 = k6;
//  } 
//  if (k7 != ok7)
//  {
//    if (k7) drawKey (2,0,'7',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,0,'7',ILI9341_WHITE, ILI9341_BLACK);
//    ok7 = k7;
//  } 
//  if (k8 != ok8)
//  {
//    if (k8) drawKey (2,1,'8',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,1,'8',ILI9341_WHITE, ILI9341_BLACK);
//    ok8 = k8;
//  } 
//  if (k9 != ok9)
//  {
//    if (k9) drawKey (2,2,'9',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,2,'9',ILI9341_WHITE, ILI9341_BLACK);
//    ok9 = k9;
//  } 
//  if (ka != oka)
//  {
//    if (ka) drawKey (3,0,'*',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,0,'*',ILI9341_WHITE, ILI9341_BLACK);
//    oka = ka;
//  } 
//  if (k0 != ok0)
//  {
//    if (k0) drawKey (3,1,'0',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,1,'0',ILI9341_WHITE, ILI9341_BLACK);
//    ok0 = k0;
//  } 
//  if (kp != okp)
//  {
//    if (kp) drawKey (3,2,'#',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,2,'#',ILI9341_WHITE, ILI9341_BLACK);
//    okp = kp;
//  }  
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == HIGH && digitalRead(IN_PIN_3) == HIGH && digitalRead(IN_PIN_4) == LOW) drawKey (0,0,'1',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,0,'1',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == HIGH && digitalRead(IN_PIN_3) == LOW  && digitalRead(IN_PIN_4) == HIGH) drawKey (0,1,'2',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,1,'2',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == LOW  && digitalRead(IN_PIN_4) == LOW) drawKey (0,2,'3',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,2,'3',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == LOW  && digitalRead(IN_PIN_2) == LOW  && digitalRead(IN_PIN_3) == LOW) drawKey (1,0,'4',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,0,'4',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == LOW  && digitalRead(IN_PIN_3) == LOW  && digitalRead(IN_PIN_4) == HIGH) drawKey (1,1,'5',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,1,'5',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == LOW  && digitalRead(IN_PIN_2) == HIGH && digitalRead(IN_PIN_3) == HIGH && digitalRead(IN_PIN_4) == HIGH) drawKey (1,2,'6',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,2,'6',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == HIGH && digitalRead(IN_PIN_3) == LOW  && digitalRead(IN_PIN_4) == LOW) drawKey (2,0,'7',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,0,'7',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == LOW  && digitalRead(IN_PIN_3) == LOW  && digitalRead(IN_PIN_4) == LOW) drawKey (2,1,'8',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,1,'8',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == LOW  && digitalRead(IN_PIN_3) == HIGH && digitalRead(IN_PIN_4) == HIGH) drawKey (2,2,'9',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,2,'9',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == HIGH && digitalRead(IN_PIN_2) == LOW  && digitalRead(IN_PIN_3) == HIGH && digitalRead(IN_PIN_4) == LOW) drawKey (3,0,'*',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,0,'*',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == LOW  && digitalRead(IN_PIN_2) == LOW && digitalRead(IN_PIN_3) == HIGH) drawKey (3,1,'0',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,1,'0',ILI9341_WHITE, ILI9341_BLACK);
  //if (digitalRead(IN_PIN_1) == LOW  && digitalRead(IN_PIN_2) == HIGH && digitalRead(IN_PIN_3) == LOW) drawKey (3,2,'#',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,2,'#',ILI9341_WHITE, ILI9341_BLACK);
  
  if (digitalRead(IN_PIN_6) == LOW) drawButton(1,ILI9341_GREEN); else drawButton(1,ILI9341_BLACK);
}

void drawKeyPress()
{
  if (k1 != ok1)
  {
    if (k1) drawKey (0,0,'1',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,0,'1',ILI9341_WHITE, ILI9341_BLACK);
    ok1 = k1;
  }
  if (k2 != ok2)
  {
    if (k2) drawKey (0,1,'2',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,1,'2',ILI9341_WHITE, ILI9341_BLACK);
    ok2 = k2;
  }
  if (k3 != ok3)
  {
    if (k3) drawKey (0,2,'3',ILI9341_BLACK, ILI9341_GREEN); else drawKey (0,2,'3',ILI9341_WHITE, ILI9341_BLACK);
    ok3 = k3;
  }
  if (k4 != ok4)
  {
    if (k4) drawKey (1,0,'4',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,0,'4',ILI9341_WHITE, ILI9341_BLACK);
    ok4 = k4;
  } 
  if (k5 != ok5)
  {
    if (k5) drawKey (1,1,'5',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,1,'5',ILI9341_WHITE, ILI9341_BLACK);
    ok5 = k5;
  } 
  if (k6 != ok6)
  {
    if (k6) drawKey (1,2,'6',ILI9341_BLACK, ILI9341_GREEN); else drawKey (1,2,'6',ILI9341_WHITE, ILI9341_BLACK);
    ok6 = k6;
  } 
  if (k7 != ok7)
  {
    if (k7) drawKey (2,0,'7',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,0,'7',ILI9341_WHITE, ILI9341_BLACK);
    ok7 = k7;
  } 
  if (k8 != ok8)
  {
    if (k8) drawKey (2,1,'8',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,1,'8',ILI9341_WHITE, ILI9341_BLACK);
    ok8 = k8;
  } 
  if (k9 != ok9)
  {
    if (k9) drawKey (2,2,'9',ILI9341_BLACK, ILI9341_GREEN); else drawKey (2,2,'9',ILI9341_WHITE, ILI9341_BLACK);
    ok9 = k9;
  } 
  if (ka != oka)
  {
    if (ka) drawKey (3,0,'*',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,0,'*',ILI9341_WHITE, ILI9341_BLACK);
    oka = ka;
  } 
  if (k0 != ok0)
  {
    if (k0) drawKey (3,1,'0',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,1,'0',ILI9341_WHITE, ILI9341_BLACK);
    ok0 = k0;
  } 
  if (kp != okp)
  {
    if (kp) drawKey (3,2,'#',ILI9341_BLACK, ILI9341_GREEN); else drawKey (3,2,'#',ILI9341_WHITE, ILI9341_BLACK);
    okp = kp;
  }  
}

void DrawUI(String i, String o)
{
  //UP
  tft.drawLine(x, y, x-20,  y+20, ILI9341_WHITE); // /
  tft.drawLine(x, y, x+20,  y+20, ILI9341_WHITE); // \
  tft.drawFastHLine(x-20,y+20,10, ILI9341_WHITE);// _
  tft.drawFastHLine(x+10,y+20,10, ILI9341_WHITE);// _
  tft.drawFastVLine(x-10,y+20,20,ILI9341_WHITE); // |
  tft.drawFastVLine(x+10,y+20,20,ILI9341_WHITE); // |
  tft.drawFastHLine(x-10,y+40,20, ILI9341_WHITE); // _
  drawUp(ILI9341_BLACK);
  //DOWN
  tft.drawLine(x, y+120, x-20,  y+100, ILI9341_WHITE); // /
  tft.drawLine(x, y+120, x+20,  y+100, ILI9341_WHITE); // \
  tft.drawFastHLine(x-20,y+100,10, ILI9341_WHITE);// _
  tft.drawFastHLine(x+10,y+100,10, ILI9341_WHITE);// _
  tft.drawFastVLine(x-10,y+80,20,ILI9341_WHITE); // |
  tft.drawFastVLine(x+10,y+80,20,ILI9341_WHITE); // |
  tft.drawFastHLine(x-10,y+80,20, ILI9341_WHITE); // _
  drawDown(ILI9341_BLACK);
  //LEFT
  tft.drawLine(x-60, y+60, x-40,  y+40, ILI9341_WHITE); // /
  tft.drawLine(x-60, y+60, x-40,  y+80, ILI9341_WHITE); // \
  tft.drawFastVLine(x-40,y+40,10,ILI9341_WHITE); // |
  tft.drawFastVLine(x-40,y+70,10,ILI9341_WHITE); // |
  tft.drawFastHLine(x-40,y+50,20,ILI9341_WHITE); // _
  tft.drawFastHLine(x-40,y+70,20,ILI9341_WHITE); // _
  tft.drawFastVLine(x-20,y+50,20, ILI9341_WHITE); // |
  drawLeft(ILI9341_BLACK);
  //RIGHT
  tft.drawLine(x+60, y+60, x+40,  y+40, ILI9341_WHITE); // \
  tft.drawLine(x+60, y+60, x+40,  y+80, ILI9341_WHITE); // /
  tft.drawFastVLine(x+40,y+40,10,ILI9341_WHITE); // |
  tft.drawFastVLine(x+40,y+70,10,ILI9341_WHITE); // |
  tft.drawFastHLine(x+20,y+50,21,ILI9341_WHITE); // _
  tft.drawFastHLine(x+20,y+70,20,ILI9341_WHITE); // _
  tft.drawFastVLine(x+20,y+50,20, ILI9341_WHITE); // |
  drawRight(ILI9341_BLACK);
  //middle
  tft.drawCircle(x,y+60,18, ILI9341_WHITE);
  // left button
  tft.drawCircle(x-45,y-15,20, ILI9341_WHITE);
  drawButton(-1, ILI9341_BLACK);
  // right button
  tft.drawCircle(x+45,y-15,20, ILI9341_WHITE);
  drawButton(1, ILI9341_BLACK);
  
  //keypad
  drawKey (0,0,'1',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (0,1,'2',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (0,2,'3',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (1,0,'4',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (1,1,'5',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (1,2,'6',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (2,0,'7',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (2,1,'8',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (2,2,'9',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (3,0,'*',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (3,1,'0',ILI9341_WHITE, ILI9341_BLACK);
  drawKey (3,2,'#',ILI9341_WHITE, ILI9341_BLACK);

  tft.setCursor(50,h-40);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print(" IN:");
  tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
  tft.println(i);
  tft.setCursor(50,h-20);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.print("OUT:");
  tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
  tft.println(o);
  

  //BROKEN SCREEN LINE???
//  tft.drawFastVLine(3,0,tft.height(),ILI9341_MAGENTA);
//  tft.drawFastVLine(4,0,tft.height(),ILI9341_BLACK); //STUCK??
//  tft.drawFastVLine(5,0,tft.height(),ILI9341_CYAN);
//
//  tft.drawFastVLine(15,0,tft.height(),ILI9341_RED);
//  tft.drawFastVLine(16,0,tft.height(),ILI9341_BLACK); //STUCK??
//  tft.drawFastVLine(17,0,tft.height(),ILI9341_BLUE);   
}

void drawKey (int row, int col, char c, uint16_t color, uint16_t bg)
{
  tft.fillRoundRect(xk+col*35+1,yk+row*35+1, 28, 28, 6, bg);
  tft.drawRoundRect(xk+col*35,yk+row*35, 30, 30, 6, color);
  tft.drawChar(xk+col*35+10, yk+8+row*35, c, color, bg, 2);
}

void drawButton (int b, uint16_t color)
{
    tft.fillCircle(x+b*45,y-15,19, color);
}

void drawUp (uint16_t color)
{
  tft.fillTriangle(x+18,y+19,x,y+1,x-18,y+19, color);
  tft.fillRect(x-9,y+20,19,20, color);
}
  
void drawDown (uint16_t color)
{
  tft.fillTriangle(x+18,y+101,x,y+119,x-18,y+101, color);
  tft.fillRect(x-9,y+81,19,20, color);
}

void drawLeft (uint16_t color)
{
  tft.fillTriangle(x-59,y+60,x-41,y+42,x-41,y+78, color);
  tft.fillRect(x-40,y+51,20,19, color);
}

void drawRight (uint16_t color)
{
  tft.fillTriangle(x+59,y+60,x+41,y+42,x+41,y+78, color);
  tft.fillRect(x+21,y+51,20,19, color);
}

