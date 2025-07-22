// SENSOR ESQUERDO
#define S0_ESQ 0        
#define S1_ESQ 1
#define S2_ESQ 2
#define S3_ESQ 3
#define OUT_ESQ 4

// SENSOR DIREITO
#define S0_DIR 13        
#define S1_DIR 12
#define S2_DIR 7
#define S3_DIR 8
#define OUT_DIR 9

struct RGB
{
    int red;
    int green;
    int blue;
};

class DCMotor
{
    int spd = 255, pin1, pin2;
  public:
    void Pinout(int in1, int in2)
    {
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
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

DCMotor Motor1;
DCMotor Motor2;

RGB lerRGB(int s2, int s3, int out)
{
    RGB cor;

    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    delay(2);
    cor.red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

    digitalWrite(s3, HIGH);
    delay(2);
    cor.blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

    digitalWrite(s2, HIGH);
    delay(2);
    cor.green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

    return cor;
}

int classificarCor(const String &cor)
{
    if (cor == "Branco") return 2;
    if (cor == "Vermelho") return 3;
    if (cor == "Verde") return 4;
    if (cor == "Preto") return 5;
    return 0;
}

String identificarCor(const RGB &cor)
{
    if (cor.red <= 14 && cor.green <= 12 && cor.blue <= 14)
        return "Branco";
    else if ((cor.red + cor.green + cor.blue) > 40)
        return "Preto";
    else if (cor.red < cor.blue && cor.red <= cor.green && cor.red < 16)
        return "Vermelho";
    else if (cor.green < cor.red && (cor.green - cor.blue) <= 8)
        return "Verde";
    else
        return "Nenhuma";
}

void imprimirCor(const String &lado, const RGB &cor)
{
    Serial.print("[" + lado + "] R:");
    Serial.print(cor.red);
    Serial.print(" G:");
    Serial.print(cor.green);
    Serial.print(" B:");
    Serial.print(cor.blue);
    Serial.print(" → ");
    Serial.println(identificarCor(cor));
}

void Direcao(int E, int D)
{
   /*
   Branco=2
   Vermelho=3
   Verde=4
   Preto=5
   */
   
    if (E == 5 && D == 5)
    {
        Motor1.Parada();
        Motor2.Parada();
    }
    else if (E == 2 && D == 2)
    {
        Motor1.Frente();
        Motor2.Frente();
    }
    else if (E > 4 && D < 4)
    {
        Motor1.Tras();
        Motor2.Frente();
    }
    else if (E < 4 && D > 4)
    {
        Motor1.Frente();
        Motor2.Tras();
    }
    else if (E == 3 && D == 3)
    {
        Motor1.Parada();
        Motor2.Parada();
        delay(10000);
    }
    else if (E == 4 && D == 4)
    {
        // Ação para verde: exemplo: marcha ré por 2 segundos
        Motor1.Tras();
        Motor2.Tras();
        delay(2000);
        Motor1.Parada();
        Motor2.Parada();
    }
    else
    {
        Serial.println("Sla como caiu aqui!!!");
    }
}

void setup()
{
    pinMode(S0_ESQ, OUTPUT);
    pinMode(S1_ESQ, OUTPUT);
    pinMode(S2_ESQ, OUTPUT);
    pinMode(S3_ESQ, OUTPUT);
    pinMode(OUT_ESQ, INPUT);

    pinMode(S0_DIR, OUTPUT);
    pinMode(S1_DIR, OUTPUT);
    pinMode(S2_DIR, OUTPUT);
    pinMode(S3_DIR, OUTPUT);
    pinMode(OUT_DIR, INPUT);

    digitalWrite(S0_ESQ, HIGH);
    digitalWrite(S1_ESQ, HIGH);
    digitalWrite(S0_DIR, HIGH);
    digitalWrite(S1_DIR, HIGH);

    Motor1.Pinout(5, 6);
    Motor2.Pinout(10, 11);

    Serial.begin(9600);
}

void loop()
{
    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    imprimirCor("Esquerda", sensorEsquerdo);
    imprimirCor("Direita ", sensorDireito);

    int corEsq = classificarCor(identificarCor(sensorEsquerdo));
    int corDir = classificarCor(identificarCor(sensorDireito));

    Direcao(corEsq, corDir);

    Serial.println("===============================");
    delay(500);
}
