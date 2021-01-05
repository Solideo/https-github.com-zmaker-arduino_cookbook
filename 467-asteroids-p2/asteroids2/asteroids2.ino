#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  pinMode(6, INPUT);
  pinMode(5, OUTPUT);
  randomSeed(analogRead(A1));
  u8g2.setFont(u8g2_font_unifont_t_symbols);    
}

int xship = 64;
int yship = 32;

//bool FIRE = false;
#define MAXCOLPI 5
int i = 0;
int xs[MAXCOLPI];
int ys[MAXCOLPI];
int ds[MAXCOLPI];
int sa[MAXCOLPI];

void loop() {
  int rot = map(analogRead(A0), 0,1023, 628,0);

  if (digitalRead(6)) {     
    ds[i] = 10;
    sa[i] = rot;
    i++;
    if (i >= MAXCOLPI) i = 0;
  }
  
  u8g2.clearBuffer();

  ship(((float)rot)/100.0f);

  //sparo
  for (int j = 0; j < MAXCOLPI; j++) {
    if (ds[j] >= 10) {
      firing(j);
      ds[j] = ds[j] + 3;  
    }
  }
  
  u8g2.sendBuffer();
  delay(50);
}

void ship(float a) {
   int x = xship + (int)10*cos(a);
   int y = yship + (int)10*sin(a);  
   int xa = xship + (int)5*cos(a + 2.0*PI / 3.0);
   int ya = yship + (int)5*sin(a + 2.0*PI / 3.0);  
   int xb = xship + (int)5*cos(a - 2.0*PI / 3.0);
   int yb = yship + (int)5*sin(a - 2.0*PI / 3.0);  
   u8g2.drawLine(xship, yship, xa, ya);
   u8g2.drawLine(xship, yship, xb, yb);
   u8g2.drawLine(x, y, xa, ya);
   u8g2.drawLine(x, y, xb, yb);
}

void firing(int i) {
   float a = ((float)sa[i])/100.0f;
   xs[i] = xship + (int)(ds[i]*cos(a));
   ys[i] = yship + (int)(ds[i]*sin(a));  
   u8g2.drawPixel(xs[i], ys[i]); 
   if ((xs[i] > 128) || (xs[i] <= 0) || (ys[i]<= 0) || (ys[i]>64)) {
     ds[i] = 0;
     xs[i] = 0;
     ys[i] = 0;
     sa[i] = 0;
   }
}
