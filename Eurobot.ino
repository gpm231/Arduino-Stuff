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
  IrReceiver.begin(5);
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
      if (last_key == W) {
        //aqui para ir hacia adelante
      }
      if (last_key == S) {
        //aqui para ir atras
      }
      if (last_key == D) {
        //aqui a la derecha
      }
      if (last_key == A) {
        //aqui a la izquierda
      }

      IrReceiver.resume();
  } else {
    current_dir = "stop";
    //aqui para parar (es lo que se ejecuta cuando dejar de pulsar)
  }

  //Serial.println(current_dir);
  delay(250);
}

void setServo(uint16_t num, int angle) {
  int frq = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(num, 0, frq);
}
