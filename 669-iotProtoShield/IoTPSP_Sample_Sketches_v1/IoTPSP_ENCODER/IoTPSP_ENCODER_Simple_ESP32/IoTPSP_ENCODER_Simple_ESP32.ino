// program to test Rotary Encoder on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number


#define RED_LED 23 	//define GPIO number for red led
#define GRN_LED 19	//define GPIO number for green led

#define ENC_SW 33	//assign pin for rotary encoder switch
#define ENC_A 27	//assign pin for rotary encoder A
#define ENC_B 35	//assign pin for rotary encoder B

int encoderPosition = 0;
int encoderLastA = LOW;
bool currentEncA = LOW;

void setup() {

  Serial.begin(9600);
  while (!Serial);             //wait for serial monitor
  delay(1000);
  Serial.println("IoTPSP Rotary Encoder");
  Serial.println(" - Rotate the encoder knob to see its incremental position changing");
  Serial.println(" - Press the encoder knob to see green led changing its status");

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_SW, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
}

void loop() {


  digitalWrite(GRN_LED, !digitalRead(ENC_SW));

  currentEncA = digitalRead(ENC_A);
  if ((encoderLastA == LOW) && (currentEncA == HIGH)) {
    if (digitalRead(ENC_B) == LOW) {
      encoderPosition--;
    } else {
      encoderPosition++;
    }
    Serial.print ("Encoder Position: ");
    Serial.println (encoderPosition);
  }
  encoderLastA = currentEncA;

}
