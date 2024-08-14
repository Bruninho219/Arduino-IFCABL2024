#include <VarSpeedServo.h>

#define servoBase   3  // Porta Digital do Servo da Base
#define servoAltura 4  // Porta Digital do Servo da Altura do Braço
#define servoAngulo 5  // Porta Digital do Servo do Ângulo do Braço
#define servoGarra  6  // Porta Digital do Servo da Garra
#define potBase    A0  // Porta Analógica do Potenciometro para Controle da base
#define potAltura  A1  // Porta Analógica do Potenciometro para Controle da altura do braço
#define potAngulo  A2  // Porta Analógica do Potenciometro para Controle do ângulo do braço
#define potGarra   A3  // Porta Analógica do Potenciometro para Controle da garra
 
//Instanciação dos Objetos de Controle dos Servos
VarSpeedServo base; 
VarSpeedServo altura;
VarSpeedServo angulo;
VarSpeedServo garra;

//Variaveis para cálculo dos angulos
int leitura_base;
int valor_base;
int leitura_altura;
int valor_altura;
int leitura_angulo;
int valor_angulo;
int leitura_garra;
int valor_garra;

void setup()
{    
  //Configuração das Portas dos Servos
  Serial.begin(9600);
  base.attach(servoBase);
  altura.attach(servoAltura);
  angulo.attach(servoAngulo);
  garra.attach(servoGarra); 
}

void loop()
{
  //###BASE###
  leitura_base = analogRead(potBase); //Leitura do Angulo do Potenciometro
  Serial.print("Potenciometro Base: ");
  Serial.println(leitura_base);
  
  valor_base = map(leitura_base, 0, 1023, 0, 180); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
  base.slowmove(valor_base, 30); //envio do ângulo para o servo
  

  //###ALTURA###
  leitura_altura = analogRead(potAltura);           //Leitura do Angulo do Potenciometro
  Serial.print("Potenciometro Altura: ");
  Serial.println(leitura_altura);
  
  valor_altura = map(leitura_altura, 0, 1023, 180, 0); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180) 
  altura.slowmove(valor_altura, 40); //envio do ângulo para o servo
  

  //###ANGULO###
  leitura_angulo = analogRead(potAngulo);           //Leitura do Angulo do Potenciometro
  Serial.print("Potenciometro Angulo: ");
  Serial.println(leitura_angulo);

  valor_angulo = map(leitura_angulo, 0, 1023, 180, 0); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
  angulo.slowmove(valor_angulo,40);                          //Envio do angulo para o Servo 
  


  //###GARRA###
  leitura_garra = analogRead(potGarra);               //Leitura do Angulo do Potenciometro
  Serial.print("Potenciometro Garra: ");
  Serial.println(leitura_garra);

  valor_garra = map(leitura_garra, 0, 1023, 0, 50); //Conversão do valor do potenciometro (de 0 até 1024) para o angulo (de 0 até 180)
  garra.slowmove(valor_garra, 40); //envio do ângulo para o servo   

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(500);
}