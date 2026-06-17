#include <Ultrasonic.h>

#define pinoUST 22
#define pinoUSE 23
#define pinoSensorIVD1 A2
#define pinoSensorIVE1 A0
#define pinoSensorIVD2 A3
#define pinoSensorIVE2 A1

const uint8_t m1=0; //esquerdo
const uint8_t m2=5; //direito
int i=0;

Ultrasonic ultrasonic(pinoUST, pinoUSE);

class DCMotor
{
  uint8_t spd = 80, pin1, pin2;
  
  public:
  void Pinout(uint8_t in1, uint8_t in2)
  {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Frente(uint8_t x)
  {
    if((spd+x)>255)
      analogWrite(pin1, 255);
    else
      analogWrite(pin1, spd+x);
    digitalWrite(pin2, LOW);
  }

  void Tras(uint8_t x)
  {
    if((spd+x)>255)
      analogWrite(pin2, 255);
    else
      analogWrite(pin2, spd+x);
    digitalWrite(pin1, LOW);

  }

  void Parada()
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1;
DCMotor Motor2;

void Direcao(int E, int D)
{
  Serial.print("[D] ");
  Serial.println(D);
  Serial.print("[E] ");
  Serial.println(E);

  /*
  Branco=0
  Preto=1
  */
  uint8_t dlRe=200;
  uint8_t dlGiro=300;
  uint8_t dlRandom=100;
  uint8_t PotenciaGiro=100;
  uint8_t dlFrente=25;
  
  
  if (E >= 1 && D >= 1)
  {
    //Frente
    Serial.println("[Frente 11]");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(dlFrente);
  }
    else if (E == 0 && D == 0)
  {
    //Frente
    Serial.println("[Frente 00]");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(dlFrente);
  }

  else if (E >= 1 && D == 0)
  {
    Serial.println("[Direita]");
    Motor1.Tras(m1);
    Motor2.Tras(m2);
    delay(dlRe);
    //Direito
    Motor1.Tras(m1+PotenciaGiro);
    Motor2.Frente(m2+PotenciaGiro);
    delay(dlGiro+random(dlRandom));

  }
  else if (E == 0 && D >= 1)
  {
    Serial.println("[Esquerda]");
    Motor1.Tras(m1);
    Motor2.Tras(m2);
    delay(dlRe);
    //Esquerdo
    Motor1.Frente(m1+PotenciaGiro);
    Motor2.Tras(m2+PotenciaGiro);
    delay(dlGiro+random(dlRandom));
  }
  else
    Serial.println("Sla como caiu aqui!!!");

  Serial.println();
}

void Desvio()
{
  int distanciaMinima = 20;

  long distancia = ultrasonic.Ranging(CM);

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if(distancia == 0)
  {
    distancia = 21;
  }

  if(distancia < distanciaMinima)
  {
    Serial.print("Obstáculo detectado a menos de ");
    Serial.print(distanciaMinima);
    Serial.println(" cm!");
    obstaculo();
  }
  else
  {
    Serial.println("Obstáculo não detectado!");
  }
}

void obstaculo()
{
    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, HIGH); // acende led vermelho
    uint8_t PotenciaGiro=50;

    digitalWrite(13, HIGH);
    int giro90=550;
    int frente=1250;
    int avanca=2500;

    Serial.println("{Iniciado o desvio!}");

    delay(50);
    Serial.println("01 Para");
    Motor1.Parada();
    Motor2.Parada();
    
    delay(100);

    digitalWrite(20, LOW); // apaga led amarelo
    Serial.println("02 Vira");
    Motor1.Tras(m1+PotenciaGiro);
    Motor2.Frente(m2+PotenciaGiro);
    delay(giro90);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("03 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("04 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(frente);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("05 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("06 Vira");
    Motor1.Frente(m1+PotenciaGiro);
    Motor2.Tras(m2+PotenciaGiro);
    delay(giro90);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("07 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("08 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(avanca);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("09 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("10 Vira");
    Motor1.Frente(m1+PotenciaGiro);
    Motor2.Tras(m2+PotenciaGiro);
    delay(giro90);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("11 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("12 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(frente);

    digitalWrite(20, HIGH); // acende led amarelo
    digitalWrite(21, LOW);  // apaga led vermelho
    Serial.println("13 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    digitalWrite(20, LOW);   // apaga led amarelo
    digitalWrite(21, HIGH);  // acende led vermelho
    Serial.println("14 Vira");
    Motor1.Tras(m1+PotenciaGiro);
    Motor2.Frente(m2+PotenciaGiro);
    delay(giro90);

    digitalWrite(20, HIGH); // acende led amarelo
    Serial.println("15 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(150);
    digitalWrite(13, LOW);

    digitalWrite(20, LOW);  // apaga led amarelo
    digitalWrite(21, LOW);  // avapaga led vermelho    
}

void setup()
{
  pinMode(20, OUTPUT);   // led amarelo
  pinMode(21, OUTPUT);   // led vermelho

  pinMode(pinoUST, OUTPUT);
  pinMode(pinoUSE, INPUT);

  pinMode(13, OUTPUT);
  pinMode(pinoSensorIVE1, INPUT);
  pinMode(pinoSensorIVD1, INPUT);
  pinMode(pinoSensorIVE2, INPUT);
  pinMode(pinoSensorIVD2, INPUT);

  Motor1.Pinout(8, 9); //esquerdo
  Motor2.Pinout(7, 6); //direito

  Serial.begin(9600);
}
void loop()
{
  int linha=180;
  Serial.print("Cont: ");
  Serial.println(i);

  int valorIVE1=analogRead(pinoSensorIVE1);
  int valorIVD1=analogRead(pinoSensorIVD1);
  int valorIVE2=analogRead(pinoSensorIVE2);
  int valorIVD2=analogRead(pinoSensorIVD2);

  Serial.print("E1 A0 *10: ");
  Serial.println(valorIVE1);
  Serial.print("D1 A2 *10: ");
  Serial.println(valorIVD1);
  
  if(valorIVE1>linha)
    valorIVE1=10;
  else
    valorIVE1=0;

  if(valorIVD1>linha)
    valorIVD1=10;
  else
    valorIVD1=0;


  Serial.print("E2 A1 *01: ");
  Serial.println(valorIVE2);
  Serial.print("D2 A3 *01: ");
  Serial.println(valorIVD2);
  
  if(valorIVE2>linha)
    valorIVE2=1;
  else
    valorIVE2=0;

  if(valorIVD2>linha)
    valorIVD2=1;
  else
    valorIVD2=0;

  //Desvio();
  Direcao(valorIVE1+valorIVE2, valorIVD1+valorIVD2);
  delay(50);

  i++;
}
