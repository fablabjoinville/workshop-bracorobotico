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

//BotaoA
#define PORT_BOTAO_A 6

//BotaoB
#define PORT_BOTAO_B 7

bool gravando = false;

//Cria um vetor bidimensional de 60 posições (para gravar 15 segundos de movimentos, 1 movimento a cada 250ms)
//por 4 posições (para guardar o angulo de cada servo)
int gavacao[60][4];
int posicaoGravacao = 0;
unsigned long  milisGravacao = 0;

bool rodandoGravacao = false;

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
  for(int i=0;i<60;i++){
    for(int j=0;j<4;j++){
      gavacao[i][j] = 90;
    }
  }
  
  Serial.begin(9600);
  pinMode(CONTROLE_HOR_DIR, INPUT);
  pinMode(CONTROLE_VER_DIR, INPUT);
  pinMode(CONTROLE_HOR_ESQ, INPUT);
  pinMode(CONTROLE_VER_ESQ, INPUT);
  pinMode(PORT_BOTAO_A, INPUT_PULLUP);
  pinMode(PORT_BOTAO_B, INPUT_PULLUP);
  
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

  //Verifica se o botao de gravação foi pressionado
  if(!digitalRead(PORT_BOTAO_A)){
    gravando = !gravando;
    if(gravando){
      Serial.println("Gravando");
      posicaoGravacao = 0;
      servoGarra.write(110);
      delay(150);
      servoGarra.write(180);
      delay(150);
      servoGarra.write(110);
      delay(150);
      servoGarra.write(180);
      delay(150);
      servoGarra.write(110);
    }
    delay(500);
  }

  //Verifica se o botao de "Play" (rodandoGravacao) 
  //foi pressionado
  if(!digitalRead(PORT_BOTAO_B)){
    rodandoGravacao = !rodandoGravacao;
    delay(500);
  }
  
  valCtrHorDir = analogRead(CONTROLE_HOR_DIR);
  valCtrVerDir = analogRead(CONTROLE_VER_DIR);
  valCtrHorEsq = analogRead(CONTROLE_HOR_ESQ);
  valCtrVerEsq = analogRead(CONTROLE_VER_ESQ);
  
  valCtrVerDir = (valCtrVerDir - 1023) * -1;
  valCtrVerEsq = (valCtrVerEsq - 1023) * -1;

  angServoGarra = map(valCtrHorEsq, 0, 1023, 0, 180);
  angServoBase = map(valCtrHorDir, 0, 1023, 0, 180);
  angServoPertoLonge = map(valCtrVerDir, 0, 1023, 0, 180);
  angServoCimaBaixo = map(valCtrVerEsq, 0, 1023, 0, 180);

  if(angServoGarra < 110){
    angServoGarra = 110;
  }
  
  servoGarra.write(angServoGarra);
  servoBase.write(angServoBase);
  servoCimaBaixo.write(angServoCimaBaixo);
  servoPertoLonge.write(angServoPertoLonge);

  //Se estiver gravando, guarda a posição dos servos a cada segundo
  if(gravando){
    if(posicaoGravacao == 59){
      Serial.println("Gravacao encerrada");
      gravando = false;
    }

    unsigned int currentMillis = millis();
    Serial.print("Gravando pos: ");
    Serial.println(posicaoGravacao);
    if((currentMillis - milisGravacao >= 250)){
      gavacao[posicaoGravacao][0] = angServoGarra;
      gavacao[posicaoGravacao][1] = angServoBase;
      gavacao[posicaoGravacao][2] = angServoCimaBaixo;
      gavacao[posicaoGravacao][3] = angServoPertoLonge;
      posicaoGravacao++;
      milisGravacao = currentMillis;
    }
  }

  //Se estuvir dando Play, executa cada um dos movimentos armazenados
  //no momento da gravação
  if(rodandoGravacao){
    Serial.println("Rodando Gravacao");
    for(int i=0;i<60;i++){
      angServoGarra = gavacao[i][0];
      angServoBase = gavacao[i][1];
      angServoCimaBaixo = gavacao[i][2];
      angServoPertoLonge = gavacao[i][3];
      servoGarra.write(angServoGarra);
      servoBase.write(angServoBase);
      servoCimaBaixo.write(angServoCimaBaixo);
      servoPertoLonge.write(angServoPertoLonge);
      delay(250);
    }
    Serial.println("Execucao da gravacao encerrada");
    rodandoGravacao = false;
  }
}
