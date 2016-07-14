#include <Servo.h>

#define CONTROLE_1 A0
#define CONTROLE_2 A1
#define CONTROLE_3 A2
#define CONTROLE_4 A3

#define PORT_SERVO_1 2
#define PORT_SERVO_2 3
#define PORT_SERVO_3 4
#define PORT_SERVO_4 5

int controle1val = 0;
int controle2val = 0;
int controle3val = 0;
int controle4val = 0;

int servo1ang = 90;
int servo2ang = 90;
int servo3ang = 90;
int servo4ang = 90;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
  pinMode(CONTROLE_1, INPUT);
  pinMode(CONTROLE_2, INPUT);
  pinMode(CONTROLE_3, INPUT);
  pinMode(CONTROLE_4, INPUT);
  servo1.attach(PORT_SERVO_1);
  servo2.attach(PORT_SERVO_2);
  servo3.attach(PORT_SERVO_3);
  servo4.attach(PORT_SERVO_4);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void loop() {
  controle1val = analogRead(CONTROLE_1);
  controle2val = analogRead(CONTROLE_2);
  controle3val = analogRead(CONTROLE_3);
  controle4val = analogRead(CONTROLE_4);

  controle1val = (controle1val - 1023) * -1;
  controle3val = (controle3val - 1023) * -1;

  servo1ang = map(controle4val, 0, 1023, 0, 180);
  servo2ang = map(controle3val, 0, 1023, 0, 180);
  servo3ang = map(controle2val, 0, 1023, 0, 180);
  servo4ang = map(controle1val, 0, 1023, 0, 180);

  if(servo1ang < 110){
    servo1ang = 110;
  }
  
  servo1.write(servo1ang);
  servo2.write(servo2ang);
  servo3.write(servo3ang);
  servo4.write(servo4ang);
}
