#include <Servo.h>

Servo servoMotor;
int led = 13;
String msg;

void setup() {   
  Serial.begin(57600);
  pinMode(led, OUTPUT);
  servoMotor.attach(2);    
}

void loop() {
  if (Serial.available() > 0) {
    delay(2);
    msg = "";
    while (Serial.available() > 0)
    //while (!msg.endsWith("%e"))
      msg += char(Serial.read());  
  }
  Serial.println(msg.toFloat()); //servoMotor.write(msg.toFloat());
}
