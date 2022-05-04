#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <IRremote.hpp>

#define SERVOMIN  120
#define SERVOMAX  620

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const long zero = 0;

const long W = -417792256;
const long S = -1387069696;
const long D = -1520763136;
const long A = -150405376;

const long pUp = -1086259456;
const long pDown = -1153106176;
const long pIn = -133693696;
const long pOut = -367657216;

long last_key = 0;

String current_dir = "stop";

void setup()
{
  IrReceiver.begin(11);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  if (IrReceiver.decode()) {
      long code = IrReceiver.decodedIRData.decodedRawData;

      //DEBUG
      //Serial.println(code);

      if (code != zero) {last_key = code;} //fixes button holding

      //MOVEMENT STUFF
      if (last_key == W) {current_dir = "forward";}
      if (last_key == S) {current_dir = "backward";}
      if (last_key == D) {current_dir = "right";}
      if (last_key == A) {current_dir = "left";}
      if (last_key == pOut) {
        Serial.println("pinzas out");
        setServo(15, 140);
        setServo(14, 60);
      }
      if (last_key == pIn) {
        Serial.println("pinzas in");
        setServo(15, 55);
        setServo(14, 135);
      }

      IrReceiver.resume();
  } else {current_dir = "stop";}

  //Serial.println(current_dir);
  delay(250);
}

void setServo(uint16_t num, int angle) {
  int frq = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(num, 0, frq);
}
