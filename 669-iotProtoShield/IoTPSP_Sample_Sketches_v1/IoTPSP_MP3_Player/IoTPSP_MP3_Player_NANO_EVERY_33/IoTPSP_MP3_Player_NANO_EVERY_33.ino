// program to test a DFPlayer Mini MP3 module on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO33 BLE, NANO33 IoT or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number


#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Serial1.begin(9600); //start additional serial port to communicate with DFPlayer Mini MP3
  
  Serial.begin(9600); //start "standard" serial port to communicate via Serial Monitor
                      //doesn't work on NANO33 BLE and NANO33 IoT

  Serial.println();
  Serial.println(F("IotPSP DFPlayer Mini MP3 Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini MP3 online."));

  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  static unsigned long timer = millis();

  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }

}
