// program to test a SERVO on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number

//To let this sketch work you need Servo library
//To use this library, open the Library Manager in the Arduino IDE and install it from there.
//more details here https://www.arduino.cc/reference/en/libraries/servo/


#include <Servo.h>

// define PIN values
#define POT_PIN A0
#define SERVO_PIN D4

const int adcMaxValue = 1024; //value of the adc to set servo at maximum Angular Position
const int adcMinValue = 0;   //minimum value of the adcValue to set servo at minimum Angular Position
const int servoMinAngularPosition = 0;  //servo minimum Angular Position in deg
const int servoMaxAngularPosition = 180;  //servo maximum Angular Position in deg

int servoPosition = 0;
int adcValue = 0;

Servo myservo;

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  delay(300);
  
  myservo.attach(SERVO_PIN);
  myservo.write(90);        // set servo to mid-point: 90°

}

void loop()
{
  adcValue = analogRead(POT_PIN);         // read the value from POT
  servoPosition = map(adcValue, adcMinValue, adcMaxValue, servoMinAngularPosition, servoMaxAngularPosition);     // scale POT value to use it with the servo (value between 0 and 180)
  myservo.write(servoPosition);     // move servo

  Serial.print("adcValue: ");
  Serial.print(adcValue);
  Serial.print(" - servoPos: ");
  Serial.println(servoPosition);
}
