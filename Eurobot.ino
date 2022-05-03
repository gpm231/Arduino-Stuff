#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <IRremote.hpp>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // 0º
#define SERVOMAX  500 // 180º
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const long zero = 0;

const long W = -1186529536;
const long S = -367657216;
const long D = -1136394496;
const long A = -1153106176;

long last_key = 0;

String current_dir = "stop";

void setup()
{
  IrReceiver.begin(11); //infrarrojos
  Serial.begin(9600); //output
  
  pwm.begin(); //servo driver
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void loop() {
  if (IrReceiver.decode()) {
      long code = IrReceiver.decodedIRData.decodedRawData;

      //DEBUG
      //Serial.println(code);

      if (code != zero) {
        last_key = code;
      } 

      //MOVEMENT STUFF
      if (last_key == W) {
        current_dir = "forward"; 
        setServo(1, 180);
        delay(1000);
      }
      if (last_key == S) {current_dir = "backward";}
      if (last_key == D) {current_dir = "right";}
      if (last_key == A) {current_dir = "left";}

      IrReceiver.resume();
  } else {current_dir = "stop";}

  Serial.println(current_dir);
  delay(250);
}

void setServo(uint8_t n_servo, int angulo) {
  int duty = map(angulo, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(n_servo, 0, duty);
}
