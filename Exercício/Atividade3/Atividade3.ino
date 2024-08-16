#define pinoBotao 2  // define pino digital D8
#define pinoLed 7    // define pino digital D7
#define pinoSensor A0

int sensorA0 = 0;
float tensao;
bool ligado = false; // define a variável ligado do tipo boleano (true ou false)

void setup()
{
  pinMode(pinoBotao, INPUT); // configura D8 como entrada digital
  pinMode(pinoLed, OUTPUT);  // configura D7 como saída digital
  Serial.begin(9600);        // monitor serial - velocidade 9600 Bps
  delay(100);                // atraso de 100 milisegundos
}

void loop()
{
  //sensorA0 = analogRead(pinoSensor);
  //tensao = sensorA0 * (5.0 / 1024);
  Serial.print("SensorA0: ");
  Serial.println(digitalRead(pinoBotao));
  
  /*
  Serial.print("SensorA0: ");
  Serial.println(sensorA0);
  Serial.print("Voltagem: ");
  Serial.println(tensao);
  */
  Serial.print("Digital2: ");
  Serial.println(digitalRead(pinoBotao));
  if(digitalRead(pinoBotao) == HIGH) // se botão for pressionado
  {
    Serial.println("Pressionado");
    if(ligado==false)                // se ligado for falso...
    {
      ligado=true;                   // ...ele fica verdadeiro7
      Serial.println("ON");
    }
    else                             // ...se não...
    {
      ligado=false;                  // ...ele fica falso
      Serial.println("OFF");
    }
    delay(200);                      // espera 200ms para evitar múltiplas leituras
  }
  if(ligado == true)
  {
    Serial.println(tensao);
    digitalWrite(7, tensao);     // acende o led
    
  }
  else
  {
    digitalWrite(pinoLed, LOW);      // desliga o led
    
  }
  
  delay(1000);                        // atraso de 100 milisegundos
}