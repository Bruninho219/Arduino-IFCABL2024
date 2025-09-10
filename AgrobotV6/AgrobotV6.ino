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

// Estrutura para cores
struct RGB
{
    int red;
    int green;
    int blue;
};

class DCMotor
{
    int spd = 96, pin1, pin2;
  public:
    void Pinout(int in1, int in2)
    {
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }

    void Frente(int x)
    {
        analogWrite(pin1, spd+x);
        digitalWrite(pin2, LOW);
    }

    void Tras(int x)
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

//Função que retorta a estrutura RGB com o nome de cor/ler a cor
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

//Apenas referencia e retorna o número correspondente a cor
int classificarCor(const String &cor)
{
    if (cor == "Branco") return 2;
    if (cor == "Vermelho") return 3;
    if (cor == "Verde") return 4;
    if (cor == "Preto") return 5;
    return 0;
}

// Aqui, com base nos valores medidos pelo sensor, ele vai verificar e decidir a cor medida
// Assim, retornando a String com o nome da cor
String identificarCor(const RGB &cor)
{
    if (cor.red <= 13 && cor.green <= 13 && cor.blue <= 13)
        return "Branco";
    else if ((cor.red + cor.green + cor.blue) > 26)
        return "Preto";
    //else if (cor.green <= cor.red && cor.green <= cor.blue)
    //    return "Verde";
    //else if (cor.red < cor.blue && cor.red <= cor.green && cor.red < 16)
    //    return "Vermelho";
    else
        return "Preto";
        //return "Nenhuma";
}

//Aqui foi usado uma referencia (&)
//Basicamente, ele mostra as cores lidas e a cor identificada
//Ex.1: [Esquerdo] R:10 G:10 B:10 → Branco
//Ex.2: [Direito] R:10 G:10 B:10 → Branco
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
   Serial.print(E);
   Serial.print(D);
   /*
   Branco=2
   Vermelho=3
   Verde=4
   Preto=5
   */
   
    if (E == 5 && D == 5) //preto
    {
        Motor1.Parada();
        Motor2.Frente(0);
        delay(500);
        Motor1.Frente(25);
        Motor2.Parada();
        delay(450);
    }
    else if (E == 2 && D == 2) //branco
    {
        //Frente
        Motor1.Frente(25);
        Motor2.Frente(0);
        delay(90);
        Motor1.Parada();
        Motor2.Parada();
        delay(50); 
    }
    else if (E > 4 && D < 4) //direita
    {   
        Motor1.Tras(25);
        Motor2.Tras(0);
        delay(40); 
        Motor1.Parada();
        Motor2.Parada();
        delay(10);
        //Direito
        Motor1.Frente(27);
        Motor2.Tras(0);
        delayMicroseconds(20+random(60));
    }
    else if (E < 4 && D > 4) //esquerda
    {
        //Esquerdo
        Motor1.Tras(27);
        Motor2.Tras(0);
        delay(40); 
        Motor1.Parada();
        Motor2.Parada();
        delay(10);
        //Esquerdo
        Motor1.Tras(27);
        Motor2.Frente(0);
        delayMicroseconds(20+random(60));
    }
    else if (E == 3 && D == 3) //vermelho
    {
        //Para por 10 segundos
        Motor1.Parada();
        Motor2.Parada();
        delay(10000);
    }
    else if (E == 4 && D == 4) //verde
    {
        // Ação para verde: exemplo: marcha ré por 2 segundos
        Motor1.Tras(24);
        Motor2.Tras(0);
        delay(1500);
        Motor1.Parada();
        Motor2.Frente(0);
        delay(1000);
    }
    else if (E == 4 && D == 2 || E == 4 && D == 5) 
    {
        Motor1.Frente(26);
        Motor2.Parada();
        delay(400);
    }
        else if (E == 2 && D == 4 || E == 5 && D == 4)
    {
        Motor1.Parada();
        Motor2.Frente(0);
        delay(400);
    }
    else
    {
        Serial.println("nada");
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

    Motor1.Pinout(6, 5);
    Motor2.Pinout(11, 10);

    Serial.begin(9600);
}

//Código começa a ser lido aqui
void loop()
{
    //Faço as leituras na função lerRGB
    //Após a leitura, esse valor é armazenado na variável sensorEsquerdo, que é do tipo RGB
    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito  = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    //Já explicada na função
    imprimirCor("Esquerda", sensorEsquerdo);
    imprimirCor("Direita ", sensorDireito);


    int corEsq = classificarCor(identificarCor(sensorEsquerdo));
    int corDir = classificarCor(identificarCor(sensorDireito));

    //Cédigo para decidir a ação dos motores
    Direcao(corEsq, corDir);
    delay(100);
    //Direcao(9,9);
    Serial.println("===============================");
    delay(50);
}   
