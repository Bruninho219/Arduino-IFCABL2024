#include <Servo.h>

#define potpin0 0
#define potpin1 1
#define potpin2 2
#define potpin3 3

Servo myservoBase; // Objeto servo para controlar a base
Servo myservoGarra; //Objeto servo para controlar a garra
Servo myservoAltura; //Objeto servo para controlar a altura do braço
Servo myservoProfundidade; //Objeto servo para profundidade a altura do braço

int val; // variable to read the value from the analog pin

void setup()
{
  Serial.begin(9600);
	myservoBase.attach(3); //Associa cada objeto a um pino pwm
	myservoGarra.attach(6);
	myservoAltura.attach(5);
	myservoProfundidade.attach(4);
}

void loop()
{
	val = map(analogRead(potpin0), 0, 1023, 0, 179);
	myservoBase.write(val);
  Serial.print("Base: ");
  Serial.println(val);
  
	val = map(analogRead(potpin1), 0, 1023, 0, 179);
	myservoAltura.write(val);
  Serial.print("Altura: ");
  Serial.println(val);

	val = map(analogRead(potpin2), 0, 1023, 0, 179);
	myservoProfundidade.write(val);
  Serial.print("Profundidade: ");
  Serial.println(val);

	val = map(analogRead(potpin3), 0, 1023, 0, 179);
	myservoGarra.write(val);
  Serial.print("Garra: ");
  Serial.println(val);


  Serial.println();
  Serial.println();
  Serial.println();
}