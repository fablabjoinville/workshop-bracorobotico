#include <Servo.h>

Servo servoGarra;
Servo servoBraco;

int potpinGarra = 0;
int potpinBraco = 1;

int valGarra;
int valBraco;

void setup() {
  servoGarra.attach(9);
  servoBraco.attach(8);
}

void loop() {
  valGarra = analogRead(potpinGarra);           
  valGarra = map(valGarra, 0, 1023, 0, 180);    
  servoGarra.write(valGarra);                 

  valBraco = analogRead(potpinBraco);           
  valBraco = map(valBraco, 0, 1023, 0, 180);    
  servoBraco.write(valBraco); 

  delay(15);
}
