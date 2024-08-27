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

  int Direcao(int E, int D, int P)
  {
    if(E < P && D < P)
    {
      return 0; //00 Frente
    }
    if(E > P && D < P)
    {
      return 10; //10 Esquerda
    }
    if(E < P && D > P)
    {
      return 1; //01 Direita
    }
    if(E > P && D > P)
    {
      return 11; //11 Parada
    }
    /*
    if(condicao para ré)
    {
      return 100; //100 Ré
    }
    */
  }
};

DCMotor Motor1, Motor2;
#define velocidade 150
#define preto 500
#define pinoSensorIVE A0
#define pinoSensorIVD A1
int valorIVE = 0;
int valorIVD = 0;
int dir = 11; //inicia parado
int time = 50; //tempo em ms que se atualiza os comandos

void setup()
{
  Motor1.Pinout(5,6);
  Motor2.Pinout(10,11);
  pinMode(pinoSensorIVE,INPUT);
  pinMode(pinoSensorIVD,INPUT);
  Serial.begin(9600);
}

void loop()
{
  Motor1.Speed(velocidade);
  Motor2.Speed(velocidade);
  valorIVD = analogRead(pinoSensorIVD);
  valorIVE = analogRead(pinoSensorIVE);
  dir = Motor1.Direcao(valorIVE, valorIVD, preto);
  Serial.print("D: ");
  Serial.println(valorIVD);
  Serial.print("E: ");
  Serial.println(valorIVE);
  Serial.println(dir);

  if(dir == 0) //00 Frente
  {
    Motor1.Frente();
    Motor2.Frente();
  }

  if(dir == 10) //01 Direita
  {
    Motor1.Frente();
    Motor2.Tras();
  }

  if(dir == 1) //10 Esquerda
  {
    Motor1.Tras();
    Motor2.Frente();
  }

  if(dir == 11) //11 Parada
  {
    Motor1.Parada();
    Motor2.Parada();
  }

  if(dir == 100) //100 Ré
  {
    Motor1.Tras();
    Motor2.Tras();
  }
  delay(time);
}