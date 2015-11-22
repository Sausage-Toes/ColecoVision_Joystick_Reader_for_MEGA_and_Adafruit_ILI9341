#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

//Define Input Pins on MEGA
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
bool input_initialized = false;
int h, w, x, y, xk, yk, xt, yt = 0;
bool k1,k2,k3,k4,k5,k6,k7,k8,k9,k0,ka,kp = false;
bool ok1,ok2,ok3,ok4,ok5,ok6,ok7,ok8,ok9,ok0,oka,okp = false;
bool p1,p2,p3,p4,p5,p6,p7,p8,p9 = false;
bool op1,op2,op3,op4,op5,op6,op7,op8,op9 =false;

bool showInputPins = true;
int inputPinDisplay_x = 30, inputPinDisplay_y = 212;
int mode = 0;


void setup() 
{
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(rotation);
  tft.fillScreen(ILI9341_BLACK);
  h = tft.height();  w = tft.width();
  Serial.print("H:"); Serial.println(h);
  Serial.print("W:");Serial.println(w);
  if (mode == 0) ts.begin();
}


void loop()
{
  if (mode == 0)
  {
    if (!input_initialized)
    {
      InitializeController_Port_All_INPUT();
      //InitializeController_Coleco_Flashback();
      //if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
      //op1=!p1,op2=!p2,op3=!p3,op4=!p4,op5=!p5,op6=!p6,op7=!p7,op8=!p8,op9=!p9;
      drawInputPins(40,60,20);
    }
    
    drawInputPins(40,60,20);

    if (ts.bufferEmpty()) 
    {
      return;
    }
     // Retrieve a point 
     TS_Point p; 
     while (ts.touched())
     {
        p = ts.getPoint();
     }


    // Scale from ~0->4000 to tft.width using the calibration #'s
    TS_Point t;
    t.x = constrain(p.x,TS_MINX,TS_MAXX);
    t.y = constrain(p.y,TS_MINY,TS_MAXY);
    //rotate x,y
    p.x = map(t.y, TS_MINY, TS_MAXY, 0, tft.width());
    p.y = map(t.x, TS_MINX, TS_MAXX, tft.height(), 0);
   
    Serial.print("("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")");
    
    if ((p.x >=  60 && p.x < 100) && (p.y >= 30  && p.y < 65 ))  
    {
      Serial.println("ONE");
      if (digitalRead(IN_PIN_1) == HIGH)
      {
        pinMode(IN_PIN_1, OUTPUT);
        digitalWrite(IN_PIN_1, LOW);
      }
      else
      {
        pinMode (IN_PIN_1, INPUT_PULLUP);
      }
    }
    
    if ((p.x >= 100 && p.x < 140) && (p.y >= 30  && p.y < 65 )) 
    {
      Serial.println("TWO");
      if (digitalRead(IN_PIN_2) == HIGH)
      {
        pinMode(IN_PIN_2, OUTPUT);
        digitalWrite(IN_PIN_2, LOW);
      }
      else
      {
        pinMode (IN_PIN_2, INPUT_PULLUP);
      }
    }
    if ((p.x >= 140 && p.x < 190) && (p.y >= 30  && p.y < 65 ))  
    {
      Serial.println("THREE");
      if (digitalRead(IN_PIN_3) == HIGH)
      {
        pinMode(IN_PIN_3, OUTPUT);
        digitalWrite(IN_PIN_3, LOW);
      }
      else
      {
        pinMode (IN_PIN_3, INPUT_PULLUP);
      }
    }
    if ((p.x >= 190 && p.x < 230) && (p.y >= 30  && p.y < 65 ))  
    {
      Serial.println("FOUR");
      if (digitalRead(IN_PIN_4) == HIGH)
      {
        pinMode(IN_PIN_4, OUTPUT);
        digitalWrite(IN_PIN_4, LOW);
      }
      else
      {
        pinMode (IN_PIN_4, INPUT_PULLUP);
      }
    }
    if ((p.x >= 230 && p.x < 280) && (p.y >= 30  && p.y < 65 ))  
    {
      Serial.println("FIVE");
      if (digitalRead(IN_PIN_5) == HIGH)
      {
        pinMode(IN_PIN_5, OUTPUT);
        digitalWrite(IN_PIN_5, LOW);
      }
      else
      {
        pinMode (IN_PIN_5, INPUT_PULLUP);
      }
    }
        
    if ((p.x >=  95 && p.x < 125) && (p.y >= 80  && p.y < 120 ))  
    {
      Serial.println("SIX");
      if (digitalRead(IN_PIN_6) == HIGH)
      {
        pinMode(IN_PIN_6, OUTPUT);
        digitalWrite(IN_PIN_6, LOW);
      }
      else
      {
        pinMode (IN_PIN_6, INPUT_PULLUP);
      }
    }
    if ((p.x >= 125 && p.x < 165) && (p.y >= 80  && p.y < 120 ))  
    {
      Serial.println("SEVEN");
      if (digitalRead(IN_PIN_7) == HIGH)
      {
        pinMode(IN_PIN_7, OUTPUT);
        digitalWrite(IN_PIN_7, LOW);
      }
      else
      {
        pinMode (IN_PIN_7, INPUT_PULLUP);
      }
    }
    if ((p.x >= 165 && p.x < 215) && (p.y >= 80  && p.y < 120 ))  
    {
      Serial.println("EIGHT");
      if (digitalRead(IN_PIN_8) == HIGH)
      {
        pinMode(IN_PIN_8, OUTPUT);
        digitalWrite(IN_PIN_8, LOW);
      }
      else
      {
        pinMode (IN_PIN_8, INPUT_PULLUP);
      }
    }
    if ((p.x >= 215 && p.x < 255) && (p.y >= 80  && p.y < 120 ))  
    {
      Serial.println("NINE");
      if (digitalRead(IN_PIN_9) == HIGH)
      {
        pinMode(IN_PIN_9, OUTPUT);
        digitalWrite(IN_PIN_9, LOW);
      }
      else
      {
        pinMode (IN_PIN_9, INPUT_PULLUP);
      }
    }
    
  }
  if (mode == 1)
  {
    if (!input_initialized)
    {
      InitializeController_Coleco();
      drawUI("Original Coleco", "n/c");
    }
    ReadJoystick_Coleco();
    ReadKeypad_Coleco();
  }
  else if (mode == 2)
  {
    if (!input_initialized)
    {
      InitializeController_Coleco_Flashback();
      drawUI("Coleco Flashback", "n/c");
    }
    ReadJoystick_Coleco_Flashback();
    ReadButtons_Coleco_Flashback();
    ReadKeypad_Coleco_Flashback();
  }
}

void InitializeController_Port_All_INPUT()
{
  pinMode (IN_PIN_1, INPUT_PULLUP); 
  pinMode (IN_PIN_2, INPUT_PULLUP); 
  pinMode (IN_PIN_3, INPUT_PULLUP); 
  pinMode (IN_PIN_4, INPUT_PULLUP); 
  pinMode (IN_PIN_5, INPUT_PULLUP); 
  pinMode (IN_PIN_6, INPUT_PULLUP); 
  pinMode (IN_PIN_7, INPUT_PULLUP); 
  pinMode (IN_PIN_8, INPUT_PULLUP);
  pinMode (IN_PIN_9, INPUT_PULLUP); 
  input_initialized = true;
}

void InitializeController_Coleco_Flashback()
{
  pinMode (IN_PIN_1, INPUT_PULLUP); // + pin2 low = RB
  pinMode (IN_PIN_2, INPUT_PULLUP); //up
  pinMode (IN_PIN_3, OUTPUT); digitalWrite(IN_PIN_3, LOW); //Common
  p3 = false; op3 = true;
  pinMode (IN_PIN_4, INPUT_PULLUP); 
  pinMode (IN_PIN_5, INPUT_PULLUP); //down
  pinMode (IN_PIN_6, INPUT_PULLUP); //left
  pinMode (IN_PIN_7, INPUT_PULLUP); //right
  pinMode (IN_PIN_8, INPUT_PULLUP); // + pin2 low = LB
  pinMode (IN_PIN_9, INPUT_PULLUP); 
  input_initialized = true;
}

void InitializeController_Coleco()
{
  pinMode (IN_PIN_1, INPUT_PULLUP); //Brown UP
  pinMode (IN_PIN_2, INPUT_PULLUP); //Red DOWN
  pinMode (IN_PIN_3, INPUT_PULLUP); //Orange LEFT
  pinMode (IN_PIN_4, INPUT_PULLUP); //Yellow RIGHT
  pinMode (IN_PIN_6, INPUT_PULLUP); //Blue BUTTON

  //Ground is switch between Pins 5 and 8 to mux Joystick with Keypad
  // JOYSTICK = Pin 5 == HIGH && Pin 8 == LOW
  // KEYPAD = Pin 5 == LOW && Pin 8 == HIGH
  pinMode (IN_PIN_5, OUTPUT);
  pinMode (IN_PIN_8, OUTPUT);
  input_initialized = true;
}

void ReadJoystick_Coleco_Flashback()
{
    if (digitalRead(IN_PIN_2) == LOW) drawUp(ILI9341_GREEN); else drawUp(ILI9341_BLACK);
    if (digitalRead(IN_PIN_5) == LOW) drawDown(ILI9341_GREEN); else drawDown(ILI9341_BLACK);
    if (digitalRead(IN_PIN_6) == LOW) drawLeft(ILI9341_GREEN); else drawLeft(ILI9341_BLACK);
    if (digitalRead(IN_PIN_7) == LOW) drawRight(ILI9341_GREEN); else drawRight(ILI9341_BLACK);
    if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
}

void ReadButtons_Coleco_Flashback()
{
  pinMode (IN_PIN_2, OUTPUT); digitalWrite(IN_PIN_2, LOW);
  if (digitalRead(IN_PIN_1) == LOW) drawButton(-1,ILI9341_GREEN); else drawButton(-1,ILI9341_BLACK);
  if (digitalRead(IN_PIN_8) == LOW) drawButton(1,ILI9341_GREEN); else drawButton(1,ILI9341_BLACK);
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
  digitalWrite(IN_PIN_2, HIGH); pinMode (IN_PIN_2, INPUT_PULLUP);
}

void ReadKeypad_Coleco_Flashback()
{
  digitalWrite(IN_PIN_3, HIGH); // mask joystick
  pinMode (IN_PIN_9, OUTPUT); digitalWrite(IN_PIN_9, LOW); 
  k1 = digitalRead(IN_PIN_5) == LOW;
  k2 = digitalRead(IN_PIN_6) == LOW;
  k3 = digitalRead(IN_PIN_7) == LOW;
    if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
  digitalWrite(IN_PIN_9, HIGH); pinMode (IN_PIN_9, INPUT_PULLUP); 

  pinMode (IN_PIN_4, OUTPUT); digitalWrite(IN_PIN_4, LOW); 
  k4 = digitalRead(IN_PIN_5) == LOW;
  k5 = digitalRead(IN_PIN_6) == LOW;
  k6 = digitalRead(IN_PIN_7) == LOW;
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
  digitalWrite(IN_PIN_4, HIGH); pinMode (IN_PIN_4, INPUT_PULLUP); 
  
  pinMode (IN_PIN_8, OUTPUT); digitalWrite(IN_PIN_8, LOW); 
  k7 = digitalRead(IN_PIN_5) == LOW;
  k8 = digitalRead(IN_PIN_6) == LOW;
  k9 = digitalRead(IN_PIN_7) == LOW;
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
  digitalWrite(IN_PIN_8, HIGH); pinMode (IN_PIN_8, INPUT_PULLUP); 
   
  pinMode (IN_PIN_1, OUTPUT); digitalWrite(IN_PIN_1, LOW); 
  ka = digitalRead(IN_PIN_5) == LOW;
  k0 = digitalRead(IN_PIN_6) == LOW;
  kp = digitalRead(IN_PIN_7) == LOW;
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
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
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
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

  if (digitalRead(IN_PIN_6) == LOW) drawButton(1,ILI9341_GREEN); else drawButton(1,ILI9341_BLACK);
  if (showInputPins) drawInputPins(inputPinDisplay_x,inputPinDisplay_y,8);
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

void drawUI(String i, String o)
{
  //H:240
  //W:320
  y = 80;
  x = w/2 - 60;
  xk = w/2 + 40;
  yk = y-25;
  xt = 50;
  //yt = h-35;
   yt = 3;
   
  //UP
  tft.drawLine(x, y, x-20,  y+20, ILI9341_WHITE); 
  tft.drawLine(x, y, x+20,  y+20, ILI9341_WHITE); 
  tft.drawFastHLine(x-20,y+20,10, ILI9341_WHITE);
  tft.drawFastHLine(x+10,y+20,10, ILI9341_WHITE);
  tft.drawFastVLine(x-10,y+20,20,ILI9341_WHITE); 
  tft.drawFastVLine(x+10,y+20,20,ILI9341_WHITE); 
  tft.drawFastHLine(x-10,y+40,20, ILI9341_WHITE); 
  drawUp(ILI9341_BLACK);
  //DOWN
  tft.drawLine(x, y+120, x-20,  y+100, ILI9341_WHITE); 
  tft.drawLine(x, y+120, x+20,  y+100, ILI9341_WHITE); 
  tft.drawFastHLine(x-20,y+100,10, ILI9341_WHITE);
  tft.drawFastHLine(x+10,y+100,10, ILI9341_WHITE);
  tft.drawFastVLine(x-10,y+80,20,ILI9341_WHITE); 
  tft.drawFastVLine(x+10,y+80,20,ILI9341_WHITE);
  tft.drawFastHLine(x-10,y+80,20, ILI9341_WHITE); 
  drawDown(ILI9341_BLACK);
  //LEFT
  tft.drawLine(x-60, y+60, x-40,  y+40, ILI9341_WHITE); 
  tft.drawLine(x-60, y+60, x-40,  y+80, ILI9341_WHITE); 
  tft.drawFastVLine(x-40,y+40,10,ILI9341_WHITE); 
  tft.drawFastVLine(x-40,y+70,10,ILI9341_WHITE); 
  tft.drawFastHLine(x-40,y+50,20,ILI9341_WHITE); 
  tft.drawFastHLine(x-40,y+70,20,ILI9341_WHITE); 
  tft.drawFastVLine(x-20,y+50,20, ILI9341_WHITE); 
  drawLeft(ILI9341_BLACK);
  //RIGHT
  tft.drawLine(x+60, y+60, x+40,  y+40, ILI9341_WHITE); 
  tft.drawLine(x+60, y+60, x+40,  y+80, ILI9341_WHITE); 
  tft.drawFastVLine(x+40,y+40,10,ILI9341_WHITE); 
  tft.drawFastVLine(x+40,y+70,10,ILI9341_WHITE);
  tft.drawFastHLine(x+20,y+50,21,ILI9341_WHITE); 
  tft.drawFastHLine(x+20,y+70,20,ILI9341_WHITE); 
  tft.drawFastVLine(x+20,y+50,20, ILI9341_WHITE); 
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
  
  tft.setCursor(xt,yt);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print(" IN:");
  tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
  tft.println(i);
  tft.setCursor(xt,yt+20);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.print("OUT:");
  tft.setTextColor(ILI9341_GREEN,ILI9341_BLACK);
  tft.println(o); 
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

void drawInputPins(int x0, int y0 , int r)
{
    int x = x0, y = y0, pad = 2*r+6;
    
    p1 = digitalRead(IN_PIN_1);
    p2 = digitalRead(IN_PIN_2);
    p3 = digitalRead(IN_PIN_3);
    p4 = digitalRead(IN_PIN_4);
    p5 = digitalRead(IN_PIN_5);
    p6 = digitalRead(IN_PIN_6);
    p7 = digitalRead(IN_PIN_7);
    p8 = digitalRead(IN_PIN_8);    
    p9 = digitalRead(IN_PIN_9);

    x=x+pad;
    if (p1 != op1)
    {
      if (!p1) drawPin(x,y,'1',ILI9341_WHITE, 0x8200, r); //brown = 0x8200
      else  drawPin(x,y,'1',ILI9341_WHITE, ILI9341_BLACK, r);
      op1  = p1;
    }
    
    x=x+pad;
    if (p2 != op2)
    {
      if (!p2) drawPin(x,y,'2',ILI9341_WHITE, ILI9341_RED, r); 
      else  drawPin(x,y,'2',ILI9341_WHITE, ILI9341_BLACK, r);
      op2  = p2;
    }

    x=x+pad;
    if (p3 != op3)
    {
      if (!p3) drawPin(x,y,'3',ILI9341_WHITE, ILI9341_ORANGE, r); 
      else  drawPin(x,y,'3',ILI9341_WHITE, ILI9341_BLACK, r);
      op3  = p3;
    }  

    x=x+pad;
    if (p4 != op4)
    {
      if (!p4) drawPin(x,y,'4',ILI9341_BLACK, ILI9341_YELLOW, r); 
      else  drawPin(x,y,'4',ILI9341_WHITE, ILI9341_BLACK, r);
      op4  = p4;
    }   
    
    x=x+pad;
    if (p5 != op5)
    {
      if (!p5) drawPin(x,y,'5',ILI9341_BLACK, ILI9341_DARKGREEN, r); 
      else  drawPin(x,y,'5',ILI9341_WHITE, ILI9341_BLACK, r);
      op5  = p5;
    }
    
    //x=x0+pad+11; y=y0+2*r+3;
    x=x0+1.5*pad; y=y0+2*r+3;
    if (p6 != op6)
    {
      if (!p6) drawPin(x,y,'6',ILI9341_BLACK, ILI9341_NAVY, r); 
      else  drawPin(x,y,'6',ILI9341_WHITE, ILI9341_BLACK, r);
      op6  = p6;
    }

    x=x+pad;
    if (p7 != op7)
    {
      if (!p7) drawPin(x,y,'7',ILI9341_BLACK, ILI9341_PURPLE, r); 
      else  drawPin(x,y,'7',ILI9341_WHITE, ILI9341_BLACK, r);
      op7  = p7;
    }

    x=x+pad;
    if (p8 != op8)
    {
      if (!p8) drawPin(x,y,'8',ILI9341_BLACK, ILI9341_DARKGREY, r); 
      else  drawPin(x,y,'8',ILI9341_WHITE, ILI9341_BLACK, r);
      op8  = p8;
    }
    
    x=x+pad;
    if (p9 != op9)
    {
      if (!p9) drawPin(x,y,'9',ILI9341_BLACK,  ILI9341_WHITE, r); 
      else  drawPin(x,y,'9',ILI9341_WHITE, ILI9341_BLACK, r);
      op9  = p9;
    } 
}

void drawPin (int x, int y, char c, uint16_t color, uint16_t bg, int r)
{
  tft.drawCircle(x,y, r, ILI9341_WHITE);
  tft.fillCircle(x,y,r-1,bg);
  tft.drawChar(x-2, y-3, c, color, bg, 1);
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
