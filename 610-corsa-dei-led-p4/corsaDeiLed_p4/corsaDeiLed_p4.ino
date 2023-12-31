#include <FastLED.h>
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

#include "DigitLedDisplay.h"
/* MAX7219 - Arduino Pin to Display Pin
   10 to DIN,
   9 to CS,
   8 to CLK */
DigitLedDisplay ld = DigitLedDisplay(10, 9, 8);

//variabili 
int lapsa, lapsb;
int xa = 0;
int vela = 0;
int prevb1, b1;

int xb = 0;
int velb = 0;
int prevb2, b2;

unsigned long t1;

int stato = 0;


void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  FastLED.addLeds<WS2812, 5, BRG>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();

  //display
  ld.setBright(10);
  ld.setDigitLimit(8);
  ld.clear();
}


void loop() {
  switch(stato) {
    case 0:
      waitstart();
      break;
    case 1:
      countdown();
      break;
    case 2:
      runcolors();
      break;
    case 3:
      winner();
      break;
  }
}

void waitstart(){
  if (digitalRead(2) && digitalRead(3)) {
    stato = 1;
    ld.clear();
  }
}

void countdown() {
  for (int i = 3; i >= 0; i--) {
    ld.printDigit(i);
    delay(1000);
  }  
  ld.clear();
  
  t1 = millis();
  xa = 0;
  xb = 0;
  lapsa = 0;
  lapsb = 0;
  vela = 0;
  velb = 0;

  stato = 2;
}

void runcolors() {
  b1 = digitalRead(2);
  if (b1 && !prevb1) {
    //FDS
    vela = 3;        
  }
  b2 = digitalRead(3);
  if (b2 && !prevb2) {
    //FDS
    velb = 3;        
  }

  if ((millis() - t1) > 100) {
    //cancello i led nella loro posizione precedente
    leds[xa] = CRGB::Black; 
    leds[xb] = CRGB::Black; 

    // BLUE
    xa += (vela > 0 ? 1 : 0);
    if (xa >= NUM_LEDS) {
      Serial.println("A");
      xa = 0;
      lapsa++;
    }
    leds[xa].setRGB(0,0,255);
    //ROSSO
    xb += (velb > 0 ? 1 : 0);
    if (xb >= NUM_LEDS) {
      Serial.println("B");
      xb = 0;
      lapsb++;
    }
    //fine a 3 giri
    if ((lapsa == 3) || (lapsb == 3)) {
      stato = 3; 
       ld.clear(); 
    }
    leds[xb].setRGB(255,0,0);

    //se le luci sono sovrapposte le coloro di viola
    if (xa == xb) leds[xa].setRGB(255,0,255);
    FastLED.show(); 

    //decremento le velocità
    if (vela > 0) {
      vela--;  
    } else if (vela < 0) {
      vela = 0;
    }
    if (velb > 0) {
      velb--;    
    } else if (velb < 0) {
      velb = 0;
    } 
    
    updateLaps();
    t1 = millis();
  }
  
  prevb1 = b1; 
  prevb2 = b2;
}

void updateLaps() {
  ld.clear();
  Serial.print(xa);
  Serial.print("-");
  Serial.print(xb);
  Serial.print("\t");
  Serial.print(lapsa);
  Serial.print("-");
  Serial.println(lapsb);
  ld.printDigit(lapsa);
  ld.printDigit(lapsb, 4);  
  
}

void winner() {
  ld.clear();
  delay(100);
  if (lapsa > lapsb) {
    ld.printDigit(11111111);
  } else {
    ld.printDigit(22222222);
  }  
  stato = 0;
}
