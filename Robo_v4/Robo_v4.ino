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
    int spd = 100, pin1, pin2;
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

//Função que retorta a estrutura RGB com o nome de cor
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

//Aqui, com base nos valores medidos pelo sensor, ele vai verificar e decidir a cor medida
//Assim, retornando a String com o nome da cor
String identificarCor(const RGB &cor)
{
    if (cor.red <= 12 && cor.green <= 12 && cor.blue <= 12)
        return "Branco";
    else if ((cor.red + cor.green + cor.blue) > 30)
        return "Preto";
    else if (cor.red < cor.blue && cor.red <= cor.green && cor.red < 16)
        return "Vermelho";
    else if (cor.green < cor.red && (cor.green - cor.blue) <= 8)
        return "Verde";
    else
        return "Nenhuma";
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

//Com base na cor, foi atribuido um numero para ele no metodo "classificarCor"
//Poderiam ter sido usado os proprios nomes, mas comparação de é diferente se não me engano
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
        //Parada
        Motor1.Frente();
        Motor2.Frente();
    }
    else if (E == 2 && D == 2)
    {
        //Frente
        Motor1.Frente();
        Motor2.Frente();
    }
    else if (E > 4 && D < 4)
    {
      //Direito
        Motor1.Tras();
        Motor2.Tras();
        delay(100);
      
        Motor1.Tras();
        Motor2.Frente();
        delay(100+random(100));
    }
    else if (E < 4 && D > 4)
    {
        //Esquerdo
        Motor1.Tras();
        Motor2.Tras();
        delay(100); 
      
        Motor1.Frente();
        Motor2.Tras();
        delay(100+random(100));
    }
    else if (E == 3 && D == 3)
    {
        //Para por 10 segundos
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

    Motor1.Pinout(6, 5);
    Motor2.Pinout(11, 10);

    Serial.begin(9600);
}

void loop()
{
    //Faço as leituras na função lerRGB
    //Após a leitura, esse valor é armazenado na variável sensorEsquerdo, que é do tipo RGB
    RGB sensorEsquerdo = lerRGB(S2_ESQ, S3_ESQ, OUT_ESQ);
    RGB sensorDireito = lerRGB(S2_DIR, S3_DIR, OUT_DIR);

    //Já explicada na função
    imprimirCor("Esquerda", sensorEsquerdo);
    imprimirCor("Direita ", sensorDireito);

    /*
        Aqui é uma função composta...
        Primeiro, crio a variável corEsq do tipo inteiro
        Segundo, essa variável vai receber o valor que está sendo retornado na função classificarCor
        Terceiro, que por sua vez, está sendo enviado o retorno de identificar cor
    
        Ex.: 
            - sensorEsquerdo: é uma variável struct, que dentro dela tem as variáveis reb, blue e green
            - identificarCor(sensorEsquerdo): nessa função, ele irá retornar o nome da cor, exemplo "Branco"
            - classificarCor("Branco"): ele retornará o número correspondente a cor, sendo o "2" nesse caso
            - por sua vez, corEsq receberá o número "2"
    */
    int corEsq = classificarCor(identificarCor(sensorEsquerdo));
    int corDir = classificarCor(identificarCor(sensorDireito));

    //Cédigo para decidir a ação dos motores
    Direcao(corEsq, corDir);
    delay(100);
    Direcao(5,5);
    Serial.println("===============================");
    delay(50);
}   
