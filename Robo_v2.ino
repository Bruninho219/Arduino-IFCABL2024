// SENSOR DIREITO
#define S0_DIR 0        
#define S1_DIR 1
#define S2_DIR 2
#define S3_DIR 3
#define OUT_DIR 4

// SENSOR ESQUERDO
#define S0_ESQ 13        
#define S1_ESQ 12
#define S2_ESQ 7
#define S3_ESQ 8
#define OUT_ESQ 9

struct RGB
{
    int red;
    int green;
    int blue;
};

struct AmostraCor
{
    int red;
    int green;
    int blue;
    String nome;
};

const AmostraCor calibragem[] = 
{
    // === PRETO ===
    {17, 17, 15, "Preto"},
    {17, 18, 16, "Preto"},
    {19, 19, 17, "Preto"},
    {16, 16, 14, "Preto"},
    {15, 16, 14, "Preto"},
    {5, 18, 17, "Preto"},
    {15, 17, 16, "Preto"},
    {13, 13, 13, "Preto"},
    {14, 14, 13, "Preto"},
    {13, 13, 12, "Preto"},
    {13, 14, 12, "Preto"},
    {14, 13, 13, "Preto"},
    {17, 11, 15, "Preto"},
    {7, 15, 14, "Preto"},
    {10, 15, 14, "Preto"},
    {6, 15, 14, "Preto"},
    {11, 12, 10, "Preto"},
    {19, 13, 17, "Preto"},
    {16, 10, 14, "Preto"},
    {14, 14, 12, "Preto"},
    {11, 18, 16, "Preto"},

    // === VERDE ===
    {22, 14, 15, "Verde"},
    {4, 14, 16, "Verde"},
    {23, 14, 15, "Verde"},
    {17, 12, 12, "Verde"},
    {24, 14, 15, "Verde"},
    {15, 12, 11, "Verde"},
    {16, 12, 12, "Verde"},
    {18, 13, 14, "Verde"},
    {20, 14, 15, "Verde"},

    // === VERMELHO ===
    {10, 24, 20, "Vermelho"},
    {9, 21, 18, "Vermelho"},
    {9, 21, 17, "Vermelho"},
    {8, 18, 15, "Vermelho"},
    {8, 17, 15, "Vermelho"},
    {8, 17, 10, "Vermelho"},
    {8, 18, 16, "Vermelho"},
    
    {3, 15, 14, "Vermelho"},
    {10, 22, 19, "Vermelho"},
    {10, 21, 19, "Vermelho"},
    {11, 23, 20, "Vermelho"},
    {10, 23, 20, "Vermelho"},
    {11, 26, 22, "Vermelho"},
    {11, 25, 21, "Vermelho"},
    {11, 27, 23, "Vermelho"},
    {12, 27, 23, "Vermelho"},
    {7, 25, 21, "Vermelho"},
    {2, 25, 22, "Vermelho"},
    {11, 19, 21, "Vermelho"},
    {11, 24, 21, "Vermelho"},
    {11, 24, 20, "Vermelho"},

    // === BRANCO ===
    {2, 7, 7, "Branco"},
    {7, 7, 7, "Branco"},
    {3, 7, 6, "Branco"},
    {2, 7, 6, "Branco"},
    {6, 6, 5, "Branco"},
    {2, 3, 7, "Branco"},
    {2, 8, 8, "Branco"},
    {8, 8, 7, "Branco"},
    {7, 6, 6, "Branco"}
};

const int NUM_AMOSTRAS = sizeof(calibragem) / sizeof(calibragem[0]);

class DCMotor
{
    int spd = 100, pin1, pin2;
  public:
    void Pinout(int in1, int in2)
    {
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }

    void Frente() { analogWrite(pin1, spd); digitalWrite(pin2, LOW); }
    void Tras()   { digitalWrite(pin1, LOW); analogWrite(pin2, spd); }
    void Parada() { digitalWrite(pin1, LOW); digitalWrite(pin2, LOW); }
};

DCMotor Motor1;
DCMotor Motor2;

RGB lerRGB(int s2, int s3, int out)
{
    RGB cor;

    digitalWrite(s2, LOW); digitalWrite(s3, LOW); delay(50);
    cor.red = pulseIn(out, LOW);

    digitalWrite(s2, LOW); digitalWrite(s3, HIGH); delay(50);
    cor.blue = pulseIn(out, LOW);

    digitalWrite(s2, HIGH); digitalWrite(s3, HIGH); delay(50);
    cor.green = pulseIn(out, LOW);

    return cor;
}

bool corAproximada(const RGB &a, const AmostraCor &b)
{
    int tolerancia = 1;
    return abs(a.red - b.red) <= tolerancia &&
           abs(a.green - b.green) <= tolerancia &&
           abs(a.blue - b.blue) <= tolerancia;
}

String buscarAmostraExistente(const RGB &cor)
{
    for (int i = 0; i < NUM_AMOSTRAS; i++)
    {
        if (corAproximada(cor, calibragem[i]))
            return calibragem[i].nome;
    }
    return "";
}

String identificarCorAvancado(const RGB &cor)
{
    int menorDistancia = 1000000;  // maior valor possível para evitar erros
    String corMaisProxima = "Nenhuma";

    Serial.print("Procurando cor para: R=");
    Serial.print(cor.red);
    Serial.print(", G=");
    Serial.print(cor.green);
    Serial.print(", B=");
    Serial.println(cor.blue);

    for (int i = 0; i < NUM_AMOSTRAS; i++)
    {
        if (calibragem[i].nome.length() == 0) continue;  // ← ignore amostras com nome vazio

        int dr = cor.red - calibragem[i].red;
        int dg = cor.green - calibragem[i].green;
        int db = cor.blue - calibragem[i].blue;

        int distancia = dr * dr + dg * dg + db * db;

        /*
        Serial.print("Amostra ");
        Serial.print(i);
        Serial.print(" (");
        Serial.print(calibragem[i].nome);
        Serial.print("): distancia = ");
        Serial.println(distancia);
        */

        if (distancia < menorDistancia)
        {
            menorDistancia = distancia;
            corMaisProxima = calibragem[i].nome;

            Serial.print(">> Atualizando corMaisProxima com: ");
            Serial.println(corMaisProxima);
        }
    }

    Serial.print("Menor distância encontrada: ");
    Serial.println(menorDistancia);
    Serial.print("Cor mais próxima: ");
    Serial.println(corMaisProxima);
    Serial.println();

    if (corMaisProxima.length() == 0)
    {
        Serial.println("⚠️ Nenhuma cor válida foi encontrada!");
    }

    return corMaisProxima;
}

int classificarCor(const String &cor)
{
    if (cor == "Branco") return 2;
    if (cor == "Vermelho") return 3;
    if (cor == "Verde") return 4;
    if (cor == "Preto") return 5;
    return 0;
}

void imprimirCor(const String &lado, const RGB &cor, const String &nomeCor)
{
    Serial.print("[");
    Serial.print(lado);
    Serial.print("] R:");
    Serial.print(cor.red);
    Serial.print(" G:");
    Serial.print(cor.green);
    Serial.print(" B:");
    Serial.print(cor.blue);
    Serial.print(" → ");
    Serial.println(nomeCor);
}

void Direcao(int E, int D)
{
    if (E == 5 && D == 5)
    {
        Motor1.Parada(); Motor2.Parada();
    }
    else if (E == 2 && D == 2)
    {
        Motor1.Frente(); Motor2.Frente();
    }
    else if (E > 4 && D < 4)
    {
        Motor1.Tras(); Motor2.Tras(); delay(100);
        Motor1.Tras(); Motor2.Frente(); delay(250);
    }
    else if (E < 4 && D > 4)
    {
        Motor1.Tras(); Motor2.Tras(); delay(100);
        Motor1.Frente(); Motor2.Tras(); delay(250);
    }
    else if (E == 3 && D == 3)
    {
        Motor1.Parada(); Motor2.Parada(); delay(10000);
    }
    else if (E == 4 && D == 4)
    {
        Motor1.Tras(); Motor2.Tras(); delay(2000);
        Motor1.Parada(); Motor2.Parada();
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

    Motor1.Pinout(6, 5);
    Motor2.Pinout(11, 10);

    Serial.begin(9600);
}

void loop()
{
    Serial.print("Total de amostras: ");
    Serial.println(NUM_AMOSTRAS);
    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    String corNomeEsq = identificarCorAvancado(sensorEsquerdo);
    String corNomeDir = identificarCorAvancado(sensorDireito);

    imprimirCor("Esquerda", sensorEsquerdo, corNomeEsq);
    imprimirCor("Direita ", sensorDireito, corNomeDir);

    int corEsq = classificarCor(corNomeEsq);
    int corDir = classificarCor(corNomeDir);

    Direcao(corEsq, corDir);
    delay(100);
    Motor1.Parada();
    Motor2.Parada();

    Serial.println("===============================");
    delay(1000);
}