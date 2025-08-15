// ULTRASSOM
#define US_TRIG A4
#define US_ECHO A5

// SENSOR ESQUERDO
#define S0_ESQ 0
#define S1_ESQ 1
#define S2_ESQ 2
#define S3_ESQ 3
#define OUT_ESQ 4

// SENSOR DIREITO
#define S0_DIR A3
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
    uint8_t spd = 90, pin1, pin2;
    
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

//Função que retorta a estrutura RGB com o nome de cor
RGB lerRGB(uint8_t s2, uint8_t s3, uint8_t out)
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
uint8_t classificarCor(const String &cor)
{
    if (cor == "Branco") return 2;
    if (cor == "Preto") return 5;
    return 0;
}

// Aqui, com base nos valores medidos pelo sensor, ele vai verificar e decidir a cor medida
// Assim, retornando a String com o nome da cor
String identificarCor(const RGB &cor)
{
    if (cor.red <= 12 && cor.green <= 12 && cor.blue <= 12)
        return "Branco";
    else return "Preto";
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

void ultrassom()
{
    float tempo=0;
    float distancia=0;
    uint8_t distanciaMinima=20;

    digitalWrite(US_TRIG, LOW); //não envia som (limpeza de ruídos)
    delayMicroseconds(2);
    digitalWrite(US_TRIG, HIGH); //envia som
    delayMicroseconds(10);
    digitalWrite(US_TRIG, LOW); //não envia o som e espera o retorno do som enviado
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
        //obstaculo();
    }
    else Serial.println("Obstáculo não detectado!");
}

void obstaculo()
{
    int giro90=1100;
    int frente=1500;
    int avanca=3500;
    uint8_t m1=3; 
    uint8_t m2=0;

    Serial.println("{Iniciado o desvio!}");

    Serial.println("01 Para");
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

    Serial.println("04 Frente");
    Motor1.Frente(m1);
    Motor2.Frente(m2);
    delay(frente);

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
}

//Com base na cor, foi atribuido um numero para ele no metodo "classificarCor"
//Poderiam ter sido usado os proprios nomes, mas comparação de é diferente se não me engano
void Direcao(uint8_t E, uint8_t D)
{
    /*
    Branco=2
    Preto=5
    Parada=9
    */

    uint8_t a=7; 
    uint8_t b=0;
    uint8_t DL=75;
    E=5;
    D=5;

    if (E == 5 && D == 5)
    {
        //Parada
        Motor1.Frente(a);
        Motor2.Frente(b);
    }
    else if (E == 2 && D == 2)
    {
        //Frente
        Motor1.Frente(a);
        Motor2.Frente(b);
    }
    else if (E == 9 && D == 9)
    {
        //Parada
        Motor1.Parada();
        Motor2.Parada();
        delay(5);
    }
    else if (E == 5 && D == 2)
    {   
        Motor1.Tras(a);
        Motor2.Tras(b);
        delay(DL);
        //Direito
        Motor1.Tras(a);
        Motor2.Frente(b);
        delay(DL+random(100));

    }
    else
    {
        Serial.println("Sla como caiu aqui!!!");
    }
}

void setup()
{
    pinMode(US_TRIG, OUTPUT);
    pinMode(US_ECHO, INPUT);

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
    ultrassom();
    //Faço as leituras na função lerRGB
    //Após a leitura, esse valor é armazenado na variável sensorEsquerdo, que é do tipo RGB
    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    //Já explicada na função
    imprimirCor("Esquerda", sensorEsquerdo);
    imprimirCor("Direita ", sensorDireito);

    uint8_t corEsq = classificarCor(identificarCor(sensorEsquerdo));
    uint8_t corDir = classificarCor(identificarCor(sensorDireito));

    //Cédigo para decidir a ação dos motores
    Direcao(corEsq, corDir);
    delay(100);
    Direcao(9,9);
    Serial.println("===============================");
    delay(50);
    delay(950);
}   