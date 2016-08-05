#include <Servo.h>

//HorizontalDireito
#define CONTROLE_HOR_DIR A1

//VerticalDireito
#define CONTROLE_VER_DIR A0

//HorizontalEsquerdo
#define CONTROLE_HOR_ESQ A2

//VerticalEsquerdo
#define CONTROLE_VER_ESQ A3

//Garra
#define PORT_SERVO_GARRA 2

//Base
#define PORT_SERVO_BASE 3

//CimaBaixo
#define PORT_SERVO_CIMABAIXO 4

//LongePerto
#define PORT_SERVO_PERTOLONGE 5

int valCtrHorDir = 0;
int valCtrVerDir = 0;
int valCtrHorEsq = 0;
int valCtrVerEsq = 0;

int angServoGarra = 90;
int angServoBase = 90;
int angServoCimaBaixo = 90;
int angServoPertoLonge = 90;

Servo servoGarra;
Servo servoBase;
Servo servoCimaBaixo;
Servo servoPertoLonge;

void setup() {
  Serial.begin(9600);
  pinMode(CONTROLE_HOR_DIR, INPUT);
  pinMode(CONTROLE_VER_DIR, INPUT);
  pinMode(CONTROLE_HOR_ESQ, INPUT);
  pinMode(CONTROLE_VER_ESQ, INPUT);
  servoGarra.attach(PORT_SERVO_GARRA);
  servoBase.attach(PORT_SERVO_BASE);
  servoCimaBaixo.attach(PORT_SERVO_CIMABAIXO);
  servoPertoLonge.attach(PORT_SERVO_PERTOLONGE);

  //Coloca todos os servos em posição de 90 graus
  servoGarra.write(110);
  servoBase.write(90);
  servoCimaBaixo.write(90);
  servoPertoLonge.write(90);
}

void loop() {
  //Le os valores de cada eixo dos joysticks
  valCtrHorDir = analogRead(CONTROLE_HOR_DIR);
  valCtrVerDir = analogRead(CONTROLE_VER_DIR);
  valCtrHorEsq = analogRead(CONTROLE_HOR_ESQ);
  valCtrVerEsq = analogRead(CONTROLE_VER_ESQ);

  //Inverte a direção
  valCtrVerDir = (valCtrVerDir - 1023) * -1;
  valCtrVerEsq = (valCtrVerEsq - 1023) * -1;

  //Converte os valores dos joystics para os valores
  //aceitos pelos servos
  angServoGarra = map(valCtrHorEsq, 0, 1023, 0, 180);
  angServoBase = map(valCtrHorDir, 0, 1023, 0, 180);
  angServoPertoLonge = map(valCtrVerDir, 0, 1023, 0, 180);
  angServoCimaBaixo = map(valCtrVerEsq, 0, 1023, 0, 180);

  //Limita o ângulo máximo
  //de abertura da garra
  if(angServoGarra < 110){
    angServoGarra = 110;
  }

  //Posiciona os servos de arcordo
  //com os ângulos convertidos
  servoGarra.write(angServoGarra);
  servoBase.write(angServoBase);
  servoCimaBaixo.write(angServoCimaBaixo);
  servoPertoLonge.write(angServoPertoLonge);
}