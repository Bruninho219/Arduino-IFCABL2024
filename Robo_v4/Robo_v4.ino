class DCMotor
{
  int spd = 255, pin1, pin2;
  public:
  void Pinout(int in1, int in2)
  {
    // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Speed(int in1)
  {
    spd = in1;
  }

  void Frente()
  {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  void Tras()
  {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  void Parada()
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1, Motor2;
#define velocidade 90
#define preto 400
#define pinoSensorIVE A0
#define pinoSensorIVD A1
#define pinoBuzzer 4
#define pinoEcho 7
#define pinoTrig 8
int valorIVE = 0;
int valorIVD = 0;
int time = 50; //tempo em ms que se atualiza os comandos
float duracao;
float distancia;

void setup()
{
  Motor1.Pinout(5,6);
  Motor2.Pinout(10,11);
  pinMode(pinoSensorIVE,INPUT);
  pinMode(pinoSensorIVD,INPUT);
  pinMode(pinoTrig, OUTPUT);
  pinMode(pinoEcho, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Motor1.Speed(velocidade);
  Motor2.Speed(velocidade);
  valorIVD = analogRead(pinoSensorIVD);
  valorIVE = analogRead(pinoSensorIVE);
  Serial.print("D: ");
  Serial.println(valorIVD);
  Serial.print("E: ");
  Serial.println(valorIVE);

  //Autor: MakerHero
 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(1000);
}// ULTRASOM + BUZZER

  //digitalWrite(pinoTrig, LOW);
 // delayMicroseconds(2);
  //digitalWrite(pinoTrig, HIGH);
  //delayMicroseconds(10);
 // digitalWrite(pinoTrig, LOW);
  
  // Calcula o tempo de retorno do pulso
 // duracao = pulseIn(pinoEcho, HIGH);
  
  // Calcula a distância em centímetros
  // 0,034 = velocidade_do_som (cm) * 10^(-6) / segundo-
/*
  if(distancia<=10)  {
    tone(pinoBuzzer, 300);

    Motor1.Frente();
    Motor2.Tras();
    delay(100);

    Motor1.Frente();
    Motor2.Frente();
    delay(100);

    Motor1.Tras();
    Motor2.Frente();
    delay(100);

    Motor1.Frente();
    Motor2.Frente();
    delay(1000);

    Motor1.Tras();
    Motor2.Frente();
    delay(100);

    Motor1.Frente();
    Motor2.Frente();
    delay(1000);

    Motor1.Frente();
    Motor2.Tras();
    delay(10);
  }
 
  else
  {
     */
    //noTone(pinoBuzzer);

  // Imprime a distância no monitor serial
  //Serial.print("Distancia: ");
  //Serial.print(distancia);
  //Serial.println(" cm");
  
  if(valorIVD < preto   && valorIVE > preto )
  {
    Motor1.Parada();
    Motor2.Frente();
    Serial.println("11111");
  }

  if(valorIVD > preto && valorIVE < preto )
  {
    Motor1.Frente();
    Motor2.Parada();
    Serial.println("22222");
  }

  if(valorIVD < preto && valorIVE < preto )
  {
    Motor1.Frente();
    Motor2.Frente();
    Serial.println("33333");
  }
  if(valorIVD > preto && valorIVE > preto )
  {
    Motor1.Parada();
    Motor2.Parada();
    Serial.println("44444");
  }

  delay(100);

  // SEGUE LINHA
  /*
  if(valorIVD > 30 && valorIVD <40)
  {
    Motor1.Frente();
    Motor2.Parada();
    delay(500);
  }
  
  if(valorIVE > 30 && valorIVE < 40)
  {
    Motor1.Parada();
    Motor2.Frente();
    delay(700);
  }
  */ 
}
