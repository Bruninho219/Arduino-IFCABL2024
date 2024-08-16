#define pinoSensor A0        // Define uma constante chamada pinoSensor com o valor A0
#define pinoLed 7

int sensorA0 = 0;            // Declara a variável sensorA0 do tipo inteiro e define 0 como valor inicial
float tensao;                // Declara a variável tensao do tipo float

void setup()
{
  pinMode(pinoLed, OUTPUT);         // configura D7 como saída digital
  pinMode(pinoSensor, INPUT);         // configura D7 como saída digital
  Serial.begin(9600);        // Inicia a comunicação serial a 9600 bps
  delay(100);                // Aguarda 100 milissegundos
}

void loop()
{
  sensorA0 = analogRead(pinoSensor);            // Lê o valor da entrada analógica A0 e armazena em sensorA0
  tensao = sensorA0 * (5.0 / 1024);             // Calcula a tensão correspondente ao valor lido
  Serial.print("Tensão do potenciômetro: ");    // Imprime uma mensagem no monitor serial
  Serial.println(tensao);                       // Imprime o valor da tensão calculada (0 - 5.0V)
  Serial.print("Valor: ");
  Serial.println(sensorA0);                     // Imprime o valor lido (0 - 1023)
  digitalWrite(pinoLed, tensao);
  Serial.println();                             // Quebra de linha
  Serial.println();
  Serial.println();
  delay(1000);                                  // Atraso de 1000 milissegundos (1 segundo)
}