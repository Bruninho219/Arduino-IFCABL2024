#define pinoSensorIVD 11
#define pinoSensorIVE 10

class DCMotor
{
  uint8_t spd = 240, pin1, pin2;
  
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

  uint8_t m1=0; 
  uint8_t m2=8;
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

void setup()
{
  pinMode(pinoSensorIVE, INPUT);
  pinMode(pinoSensorIVD, INPUT);

  Motor1.Pinout(9, 8);
  Motor2.Pinout(6, 7);

  Serial.begin(9600);
}

//Código começa a ser lido aqui
void loop()
{
  int valorIVD = digitalRead(pinoSensorIVD);
  int valorIVE = digitalRead(pinoSensorIVE);

  //Código para decidir a ação dos motores
  Direcao(valorIVE, valorIVD);
  delay(50);
}