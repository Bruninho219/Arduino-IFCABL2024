//wokwi.com/projects/406377174549881857
#define pinoBotao 8  // define pino digital D8
#define pinoLed 7    // define pino digital D7

bool ligado = false; // define a variável ligado do tipo boleano (true ou false)

void setup()
{
  pinMode(pinoBotao, INPUT_PULLUP); // configura D8 como entrada digital
  pinMode(pinoLed, OUTPUT);  // configura D7 como saída digital
  Serial.begin(9600);        // monitor serial - velocidade 9600 Bps
  delay(100);                // atraso de 100 milisegundos
}

void loop()
{
  int est = digitalRead(pinoBotao);
  
  if(digitalRead(pinoBotao) == HIGH) // se botão for pressionado
  {
    if(ligado==false)                // se ligado for falso...
    {
      ligado=true;                   // ...ele fica verdadeiro
    }
    else                             // ...se não...
    {
      ligado=false;                  // ...ele fica falso
    }
    delay(200);                      // espera 200ms para evitar múltiplas leituras
  }

  if(ligado == true)
  {
    digitalWrite(pinoLed, HIGH);     // acende o led
  }
  else
  {
    digitalWrite(pinoLed, LOW);      // desliga o led
  }
  
  delay(100);                        // atraso de 100 milisegundos
}