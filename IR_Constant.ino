#include <IRremote.hpp>

const long zero = 0;

const long W = -1186529536;
const long S = -367657216;
const long D = -1136394496;
const long A = -1153106176;

long last_key = 0;

String current_dir = "stop";

void setup()
{
  IrReceiver.begin(11);
  Serial.begin(9600);
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

      IrReceiver.resume();
  } else {current_dir = "stop";}

  Serial.println(current_dir);
  delay(250);
}
