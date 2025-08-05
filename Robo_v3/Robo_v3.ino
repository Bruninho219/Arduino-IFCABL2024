// ULTRASSOM
#define US_TRIG A0
#define US_ECHO A1

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

// PARÂMETROS MOTORES
#define RAND 100   //Valor randomico máximo
#define SPD 100 //potência para o motor 

struct RGB
{
    int red;
    int green;
    int blue;
};

struct AmostraCor
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    char nome;
};

const AmostraCor calibragemB[] = 
{
  {19, 19, 15, 'B'},
  {19, 19, 17, 'B'},
  {19, 18, 10, 'B'},
  {18, 12, 16, 'B'},
  {23, 21, 19, 'B'},
  {24, 24, 22, 'B'},
  {21, 21, 18, 'B'},
  {21, 15, 18, 'B'},
  {20, 20, 11, 'B'},
  {23, 17, 20, 'B'},
  {18, 23, 20, 'B'},
  {24, 23, 15, 'B'},
  {17, 15, 14, 'B'},
  {17, 18, 16, 'B'},
  {23, 24, 20, 'B'},
  {31, 32, 28, 'B'},
  {35, 33, 30, 'B'},
  {28, 26, 24, 'B'},
  {26, 21, 22, 'B'},
  {17, 21, 18, 'B'},
  {22, 22, 17, 'B'},
  {20, 14, 18, 'B'},
  {19, 20, 18, 'B'},
  {21, 21, 19, 'B'},
  {25, 24, 21, 'B'},
  {23, 24, 20, 'B'},
  {18, 17, 15, 'B'},
  {16, 17, 15, 'B'},
  {27, 28, 25, 'B'},
  {30, 31, 21, 'B'},
  {23, 22, 20, 'B'},
  {17, 20, 16, 'B'},
  {23, 26, 20, 'B'},
  {23, 27, 23, 'B'},
  {21, 28, 25, 'B'},
  {28, 30, 25, 'B'},
  {28, 20, 15, 'B'},
  {15, 14, 14, 'B'},
  {21, 23, 20, 'B'},
  {15, 22, 19, 'B'},
  {25, 26, 22, 'B'},
  {19, 23, 21, 'B'},
  {21, 25, 19, 'B'},
  {27, 22, 21, 'B'},
  {19, 27, 22, 'B'},
  {28, 22, 24, 'B'},
  {26, 26, 17, 'B'},
  {27, 27, 23, 'B'},
  {27, 24, 24, 'B'}
};

const AmostraCor calibragemW[] = 
{
  {7, 6, 7, 'W'},
  {1, 2, 3, 'W'},
  {4, 4, 4, 'W'},
  {8, 7, 6, 'W'},
  {6, 7, 6, 'W'},
  {11, 9, 8, 'W'},
  {8, 9, 7, 'W'},
  {3, 3, 3, 'W'},
  {8, 0, 7, 'W'},
  {7, 7, 11, 'W'},
  {3, 8, 7, 'W'},
  {8, 8, 7, 'W'},
  {9, 4, 8, 'W'},
  {1, 1, 1, 'W'},
  {3, 6, 5, 'W'},
  {5, 5, 5, 'W'},
  {6, 2, 6, 'W'},
  {0, 6, 6, 'W'},
  {6, 6, 3, 'W'},
  {9, 11, 9, 'W'}
};

const AmostraCor calibragemG[] = 
{
  {20, 8, 15, 'G'},
  {23, 7, 15, 'G'},
  {16, 12, 12, 'G'},
  {22, 14, 14, 'G'},
  {20, 13, 14, 'G'},
  {12, 13, 12, 'G'},
  {13, 11, 11, 'G'},
  {24, 14, 15, 'G'},
  {26, 15, 16, 'G'},
  {18, 12, 12, 'G'},
  {24, 16, 16, 'G'},
  {17, 14, 13, 'G'},
  {16, 14, 15, 'G'},
  {23, 8, 15, 'G'},
  {22, 15, 9, 'G'},
  {25, 12, 16, 'G'},
  {22, 14, 16, 'G'},
  {23, 12, 12, 'G'},
  {20, 15, 16, 'G'},
  {20, 14, 12, 'G'},
  {18, 14, 16, 'G'},
  {26, 12, 13, 'G'},
  {16, 13, 10, 'G'},
  {14, 15, 14, 'G'},
  {21, 12, 12, 'G'},
  {12, 13, 12, 'G'},
  {14, 14, 12, 'G'}
};

const AmostraCor calibragemR[] = 
{
  {10, 23, 19, 'R'},
  {10, 25, 20, 'R'},
  {4, 24, 20, 'R'},
  {10, 21, 17, 'R'},
  {9, 16, 13, 'R'},
  {10, 19, 16, 'R'},
  {9, 17, 15, 'R'},
  {10, 12, 14, 'R'},
  {9, 15, 17, 'R'},
  {9, 21, 14, 'R'},
  {9, 20, 12, 'R'},
  {10, 19, 19, 'R'},
  {10, 24, 14, 'R'},
  {11, 26, 14, 'R'},
  {10, 21, 19, 'R'},
  {10, 23, 16, 'R'},
  {7, 20, 16, 'R'},
  {10, 17, 17, 'R'},
  {9, 20, 10, 'R'},
  {4, 20, 17, 'R'},
  {9, 18, 11, 'R'},
  {9, 13, 11, 'R'},
  {10, 19, 14, 'R'},
  {9, 15, 7, 'R'},
  {10, 17, 19, 'R'}
};

const int NUM_PRETO = sizeof(calibragemB) / sizeof(calibragemB[0]);
const int NUM_BRANCO = sizeof(calibragemW) / sizeof(calibragemW[0]);
const int NUM_VERMELHO = sizeof(calibragemR) / sizeof(calibragemR[0]);
const int NUM_VERDE = sizeof(calibragemG) / sizeof(calibragemG[0]);

class DCMotor
{
  uint8_t pin1, pin2;
  public:
    void Pinout(uint8_t in1, uint8_t in2)
    {
        pin1 = in1;
        pin2 = in2;
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
    }

    void Frente()
    {
        analogWrite(pin1, SPD);
        digitalWrite(pin2, LOW);
    }
    void Tras()
    {
        digitalWrite(pin1, LOW);
        analogWrite(pin2, SPD);
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
    delay(50);
    cor.red = pulseIn(out, LOW);

    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    delay(50);
    cor.blue = pulseIn(out, LOW);

    digitalWrite(s2, HIGH);
    digitalWrite(s3, HIGH);
    delay(50);
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

char buscarAmostraExistente(const RGB &cor)
{
    for (int i = 0; i < NUM_PRETO; i++)
        if (corAproximada(cor, calibragemB[i]))
            return calibragemB[i].nome;

    for (int i = 0; i < NUM_BRANCO; i++)
        if (corAproximada(cor, calibragemW[i]))
            return calibragemW[i].nome;

    for (int i = 0; i < NUM_VERDE; i++)
        if (corAproximada(cor, calibragemG[i]))
            return calibragemG[i].nome;

    for (int i = 0; i < NUM_VERMELHO; i++)
        if (corAproximada(cor, calibragemR[i]))
            return calibragemR[i].nome;

    return 'D'; // D= Desconhecido
}

char identificarCorAvancado(const RGB &cor)
{
    if(cor.red<11 && cor.green<11 && cor.blue<11)
        return 'W';
    if(cor.red>=17 && cor.green>=17 && cor.blue>=17)
        return 'B';
    
    int menorDistancia = 1000000;
    char corMaisProxima = 'D';

    auto verificarDistancia = [&](const AmostraCor *amostras, int tamanho)
    {
        for (int i = 0; i < tamanho; i++)
        {
            int dr = cor.red - amostras[i].red;
            int dg = cor.green - amostras[i].green;
            int db = cor.blue - amostras[i].blue;

            int distancia = dr * dr + dg * dg + db * db;

            if (distancia < menorDistancia)
            {
                menorDistancia = distancia;
                corMaisProxima = amostras[i].nome;
            }
        }
    };

    verificarDistancia(calibragemB, NUM_PRETO);
    verificarDistancia(calibragemW, NUM_BRANCO);
    verificarDistancia(calibragemG, NUM_VERDE);
    verificarDistancia(calibragemR, NUM_VERMELHO);

    return corMaisProxima;
}

uint8_t classificarCor(char cor)
{
    switch (cor)
    {
        case 'W': return 2;
        case 'R': return 3;
        case 'G': return 4;
        case 'B': return 5;
        default:  return 0;
    }
}

void imprimirCor(bool l, const RGB &cor, char nomeCor)
{
    if(l) Serial.print("[Direito] R:");
    else Serial.print("[Esquerdo] R:");

    Serial.print(cor.red);
    Serial.print(" G:");
    Serial.print(cor.green);
    Serial.print(" B:");
    Serial.print(cor.blue);
    Serial.print(" → ");
    switch (nomeCor)
    {
        case 'W': Serial.println("Branco"); break;
        case 'R': Serial.println("Vermelho"); break;
        case 'G': Serial.println("Verde"); break;
        case 'B': Serial.println("Preto"); break;
        default:  Serial.println("Desconhecida"); break;
    }
}

bool deteccao()
{
    float tempo=0;
    float distancia=0;
    uint8_t distanciaMinima=10;

    // Gera um pulso ultrassônico
    digitalWrite(US_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(US_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(US_TRIG, LOW);

    // Calcula o tempo de retorno do pulso
    tempo = pulseIn(US_ECHO, HIGH);

    // Calcula a distância em centímetros
    // 0,034 = velocidade_do_som (cm) * 10^(-6) / segundo
    distancia = tempo * 0.034029 / 2;
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");
    
    if(distancia<distanciaMinima)
    {
        Serial.print("Obstáculo detectado a menos de ");
        Serial.print(distanciaMinima);
        Serial.println("cm!");
        obstaculo();
        return true;
    }
    Serial.println("Obstáculo não detectado!");
    return false; 
}

void obstaculo()
{
    //Comando para desviar de objeto
    Serial.println("{Desvio!}");

    Direcao(0, 0,  1, 0, true); //Ré por 1 * 100ms
    Direcao(9, 0, 10, 0, true); //Direito por 10 * 100ms
    Direcao(2, 2, 20, 0, true); //Frente por 20 * 100ms
    Direcao(5, 5,  1, 0, true); //Para por 1 * 100ms
    Direcao(0, 9, 10, 0, true); //Esquerdo por 10 * 100ms
    Direcao(2, 2, 40, 0, true); //Frente por 40 * 100ms
    Direcao(5, 5,  1, 0, true); //Para por 1 * 100ms
    Direcao(0, 9, 10, 0, true); //Esquerdo por 10 * 100ms
    Direcao(2, 2, 20, 0, true); //Frente por 20 * 100ms
    Direcao(9, 0, 10, 0, true); //Direito por 10 * 100ms
    
}

void Direcao(uint8_t E, uint8_t D, uint8_t M, uint8_t R, bool O)
{
    //M = Multiplicador
    //R = Randomico
    Serial.print("Obstáculo*: ");
    Serial.println(O);

    //2=Branco
    //3=Vermelho
    //4=Verde
    //5=Preto
    //0=Ré

    //Ignora verde e vermelho por enquanto
    if(E==2) E=2;
    else E=5;
    if(D==2) D=2;
    else D=5;

    if (E == 5 && D == 5)
    {
        //PARA
        Serial.println("{Parada}");
        Motor1.Parada();
        Motor2.Parada();
        if(O) delay(M*100-100);
    }
    else if (E == 0 && D == 0)
    {
        //RÉ
        Serial.println("{Ré}");
        Motor1.Tras();
        Motor2.Tras();
        delay(100*M);
    }
    else if ((E == 2 && D == 2) || (E == 2 && D == 3) || (E == 3 && D == 2))
    {
        //FRETE
        Serial.println("{Frente}");
        Motor1.Frente();
        Motor2.Frente();
        if(O) delay(M*100-100);
    }
    else if (E > 3 && D < 4)
    {
        //DIREITO
        Serial.println("{Direito}");
        Direcao(0, 0, 1, 0, false); //Ré por 1 * 100ms

        Motor1.Frente();
        Motor2.Tras();
        if (O) delay(R);
        else delay(100*O);
    }
    else if (E < 4 && D > 3)
    {
        //ESQUERDO
        Serial.println("{Esquerdo}");
        Direcao(0, 0, 1, 0, false); //Ré por 1 * 100ms

        Motor1.Tras();
        Motor2.Frente();
        if (O) delay(R);
        else delay(100*O);

    }
    else if (E == 3 && D == 3)
    {
        //PARA POR 10 SEGUNDOS
        Motor1.Parada();
        Motor2.Parada();
        delay(10000);
    }
    else if (E == 4 && D == 4)
    {
        //RÉ POR 2 SEGUNDOS
        Motor1.Tras();
        Motor2.Tras();
        delay(2000);
        Motor1.Parada();
        Motor2.Parada();
    }
    
    else if (E == 4 && D == 5)
    {
        Motor1.Tras();
        Motor2.Tras();
        delay(2000);
        Motor1.Tras();
        Motor2.Frente();
        delay(2000);
    }
    else if (E == 5 && D == 4)
    {
        Motor1.Tras();
        Motor2.Tras();
        delay(200);
        Motor1.Tras();
        Motor2.Frente();
        delay(2000);
    }
    else
    {
        Serial.println("Sla como caiu aqui!!!");
    }
}

void setup()
{
    pinMode(US_ECHO, INPUT);
    pinMode(US_TRIG, OUTPUT);

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
    //bool D=false; //Detecção

    Serial.println("Total de amostras: ");
    Serial.print("Preto: ");
    Serial.println(NUM_PRETO);
    Serial.print("Branco: ");
    Serial.println(NUM_BRANCO);
    Serial.print("Verde: ");
    Serial.println(NUM_VERDE);
    Serial.print("Vermelho: ");
    Serial.println(NUM_VERMELHO);

    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito  = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    char corNomeEsq='D';
    char corNomeDir='D';

    if(buscarAmostraExistente(sensorEsquerdo)=='D')
        corNomeEsq = identificarCorAvancado(sensorEsquerdo);
    else
        corNomeEsq = buscarAmostraExistente(sensorEsquerdo);
    
    if(buscarAmostraExistente(sensorDireito)=='D')
        corNomeDir = identificarCorAvancado(sensorDireito);
    else
        corNomeDir = buscarAmostraExistente(sensorDireito);

    imprimirCor(true, sensorEsquerdo, corNomeEsq);
    imprimirCor(false, sensorDireito, corNomeDir);

    uint8_t corEsq = classificarCor(corNomeEsq);
    uint8_t corDir = classificarCor(corNomeDir);

    //D=deteccao();

    Serial.print("Obstáculo: ");
    //Serial.println(D);
    Serial.println(deteccao());

    //Direcao(uint8_t E, uint8_t D, uint8_t M, uint8_t R, bool O)
    //Direcao(corEsq, corDir, 1, random(RAND), D);
    Direcao(corEsq, corDir, 1, random(RAND), false);
    delay(100);

    Motor1.Parada();
    Motor2.Parada();
    delay(2);
    Serial.println("===============================");
    //delay(1000);
}


