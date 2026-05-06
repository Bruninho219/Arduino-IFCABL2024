#include <Ultrasonic.h>

#define pinoUST 4
#define pinoUSE 5
#define pinoSensorIVD 3
#define pinoSensorIVE 2

const uint8_t m1=0; 
const uint8_t m2=8;
int i=0;

//Ultrasonic ultrasonic(pinoUST, pinoUSE);
Ultrasonic ultrasonic(4, 5);

class DCMotor
{
  uint8_t spd = 150, pin1, pin2;
  
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
    analogWrite(pin1, spd+x);
    digitalWrite(pin2, LOW);
  }

  void Tras(uint8_t x)
  {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd+x);
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
  uint8_t dlRe=50;
  uint8_t dlGiro=75;
  uint8_t dlRandom=50;
  
  if (E == 1 && D == 1)
  {
    //Frente
    Motor1.Frente(m1);
    Motor2.Frente(m2);
  }
    else if (E == 0 && D == 0)
  {
    //Frente
    Motor1.Frente(m1);
    Motor2.Frente(m2);
  }

  else if (E == 1 && D == 0)
  {   
    Motor1.Tras(m1);
    Motor2.Tras(m2);
    delay(dlRe);
    //Direito
    Motor1.Tras(m1);
    Motor2.Frente(m2);
    delay(dlGiro+random(dlRandom));

  }
  else if (E == 0 && D == 1)
  {   
    Motor1.Tras(m1);
    Motor2.Tras(m2);
    delay(dlRe);
    //Esquerdo
    Motor1.Frente(m1);
    Motor2.Tras(m2);
    delay(dlGiro+random(dlRandom));
  }
  else
    Serial.println("Sla como caiu aqui!!!");
}

void Desvio()
{
  int distanciaMinima=20;
  //long microsec = ultrasonic.timing();
  digitalWrite(pinoUST, LOW);
  delayMicroseconds(2);

  digitalWrite(pinoUST, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoUST, LOW);

  long duration = pulseIn(pinoUSE, HIGH, 30000);

  /*float distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  int distancia = ultrasonic.read();
  */
    
  long distancia = duration * 0.034 / 2;
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if(distancia<distanciaMinima)
  {
      Serial.print("Obstáculo detectado a menos de ");
      Serial.print(distanciaMinima);
      Serial.println("cm!");
      obstaculo();
  }
  else Serial.println("Obstáculo não detectado!");
}

void obstaculo()
{
    digitalWrite(13, HIGH);
    int giro90=550;
    int frente=750;
    int avanca=2500;

    Serial.println("{Iniciado o desvio!}");

   /* Serial.println("01 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("02 Vira");
    Motor1.Tras(m1);
    Motor2.Frente(m2);
    delay(giro90);

    Serial.println("03 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);
*/
    Serial.println("04 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(frente);
/*
    Serial.println("05 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("06 Vira");
    Motor1.Frente(m1);
    Motor2.Tras(m2);
    delay(giro90);

    Serial.println("07 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("08 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(avanca);

    Serial.println("09 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("10 Vira");
    Motor1.Frente(m1);
    Motor2.Tras(m2);
    delay(giro90);

    Serial.println("11 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("12 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(frente);

    Serial.println("13 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);

    Serial.println("14 Vira");
    Motor1.Tras(m1);
    Motor2.Frente(m2);
    delay(giro90);

    Serial.println("15 Para");
    Motor1.Parada();
    Motor2.Parada();
    delay(100);
    digitalWrite(13, LOW);
    */
}

void setup()
{
  pinMode(pinoUST, OUTPUT);
  pinMode(pinoUSE, INPUT);

  pinMode(13, OUTPUT);
  pinMode(pinoSensorIVE, INPUT);
  pinMode(pinoSensorIVD, INPUT);

  Motor1.Pinout(8, 9);
  Motor2.Pinout(6, 7);

  Serial.begin(9600);
}
void loop()
{
  int valorIVD = digitalRead(pinoSensorIVD);
  int valorIVE = digitalRead(pinoSensorIVE);

  //Desvio();
  Direcao(valorIVE, valorIVD);
  delay(50);
  Serial.print("Cont: ");
  Serial.println(i);
  i++;
}
