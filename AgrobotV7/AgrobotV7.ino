#include <Ultrasonic.h>

#define pinoUST 5
#define pinoUSE 4
#define pinoSensorIVD 3
#define pinoSensorIVE 2

const uint8_t m1=0; //esquerdo
const uint8_t m2=5; //direito
int i=0;

//Ultrasonic ultrasonic(pinoUST, pinoUSE);
Ultrasonic ultrasonic(pinoUST, pinoUSE);

class DCMotor
{
  uint8_t spd = 100, pin1, pin2;
  
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
  Serial.println();

  /*
  Branco=0
  Preto=1
  */
  uint8_t dlRe=100;
  uint8_t dlGiro=500;
  uint8_t dlRandom=150;
  uint8_t PotenciaGiro=100;
  uint8_t dlFrente=100;
  
  
  if (E == 1 && D == 1)
  {
    //Frente
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(dlFrente);
    Motor1.Parada();
    Motor2.Parada();
    delay(50);
  }
    else if (E == 0 && D == 0)
  {
    //Frente
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(dlFrente);
    Motor1.Parada();
    Motor2.Parada();
    delay(50);
  }

  else if (E == 1 && D == 0)
  {   
    Motor1.Tras(m1);
    Motor2.Tras(m2);
    delay(dlRe);
    //Direito
    Motor1.Tras(m1+PotenciaGiro);
    Motor2.Frente(m2+PotenciaGiro);
    delay(dlGiro+random(dlRandom));

  }
  else if (E == 0 && D == 1)
  {   
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
    digitalWrite(21, LOW);  // apaga led vermelho    
}

void setup()
{
  pinMode(20, OUTPUT);   // led amarelo
  pinMode(21, OUTPUT);   // led vermelho

  pinMode(pinoUST, OUTPUT);
  pinMode(pinoUSE, INPUT);

  pinMode(13, OUTPUT);
  pinMode(pinoSensorIVE, INPUT);
  pinMode(pinoSensorIVD, INPUT);

  Motor1.Pinout(8, 9); //esquerdo
  Motor2.Pinout(7, 6); //direito

  Serial.begin(9600);
}
void loop()
{
  int valorIVD = digitalRead(pinoSensorIVD);
  int valorIVE = digitalRead(pinoSensorIVE);

  Desvio();
  Direcao(valorIVE, valorIVD);
  delay(50);
  Serial.print("Cont: ");
  Serial.println(i);
  i++;
}
