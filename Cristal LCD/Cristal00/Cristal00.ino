//https://deepbluembedded.com/lcd-custom-character-generator/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int l = 5;

uint8_t Char0[8]; //00 00
uint8_t Char1[8]; //X0 00
uint8_t Char2[8]; //0X 00
uint8_t Char3[8]; //00 X0
uint8_t Char4[8]; //00 0X
uint8_t Char5[8]; //extra
uint8_t Char6[8]; //extra
uint8_t Char7[8]; //extra

// envia os arrays atuais e atualiza na memória para o LCD
void AtualizaLCD()
{
  lcd.createChar(0, Char0); //00 00
  lcd.createChar(1, Char1); //X0 00
  lcd.createChar(2, Char2); //0X 00
  lcd.createChar(3, Char3); //00 X0
  lcd.createChar(4, Char4); //00 0X
  lcd.createChar(5, Char5);
  lcd.createChar(6, Char6);
  lcd.createChar(7, Char7);
}

// restaura os arrays para o estado inicial
void Padrao()
{
  uint8_t c0[8] = {0,0,0,0,0,0,0,0}; //00 00
  uint8_t c1[8] = {0x07,0x08,0x10,0x10,0x10,0x10,0x10,0x10}; //X0 00
  uint8_t c2[8] = {0x1c,0x02,0x01,0x01,0x01,0x01,0x01,0x01}; //0X 00
  uint8_t c3[8] = {0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x07}; //00 X0
  uint8_t c4[8] = {0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x1c}; //00 0X

  uint8_t vazio[8] = {0,0,0,0,0,0,0,0};

  memcpy(Char0,c0,8);
  memcpy(Char1,c1,8);
  memcpy(Char2,c2,8);
  memcpy(Char3,c3,8);
  memcpy(Char4,c4,8);

  memcpy(Char5,vazio,8);
  memcpy(Char6,vazio,8);
  memcpy(Char7,vazio,8);
}

// desenha os olhos usando os chars atuais
void DesenhaOlhos()
{
  lcd.setCursor(l,0); //X0 00
  lcd.write(byte(1));

  lcd.setCursor(l+1,0); //0X 00
  lcd.write(byte(2));

  lcd.setCursor(l,1); //00 X0
  lcd.write(byte(3));

  lcd.setCursor(l+1,1); //00 0X
  lcd.write(byte(4));


  lcd.setCursor(l+4,0); //X0 00
  lcd.write(byte(1));

  lcd.setCursor(l+5,0); //0X 00
  lcd.write(byte(2));

  lcd.setCursor(l+4,1); //00 X0
  lcd.write(byte(3));

  lcd.setCursor(l+5,1); //00 0X
  lcd.write(byte(4));
}

// olhos abertos (estado padrão)
void Abertos()
{
  Padrao();       // restaura arrays
  AtualizaLCD();  // envia ao LCD
  DesenhaOlhos(); // exibe
}

// exemplo: olhando para direita
void OlhandoDir()
{
  Padrao(); // começa do padrão

  uint8_t c2[8] = {0x1c,0x02,0x01,0x01,0x03,0x07,0x07,0x07}; // Direita Cima
  uint8_t c4[8] = {0x07,0x07,0x07,0x07,0x03,0x01,0x02,0x1c}; // Direita Baixo

  memcpy(Char2,c2,8);
  memcpy(Char4,c4,8);
  AtualizaLCD();

  DesenhaOlhos();
}

void OlhandoEsq()
{
  Padrao(); // começa do padrão

  uint8_t c1[8] = {0x07,0x08,0x10,0x10,0x18,0x1c,0x1c,0x1c}; // Esquerda Cima
  uint8_t c3[8] = {0x1c,0x1c,0x1c,0x1c,0x18,0x10,0x08,0x07}; // Esquerda Baixo

  memcpy(Char1,c1,8);
  memcpy(Char3,c3,8);
  AtualizaLCD();
  
  DesenhaOlhos();
}

void PiscandoDir()
{
  Padrao();
  
  uint8_t c5[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x1c}; //...,
  uint8_t c6[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f}; //...
  uint8_t c7[] = {0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // '

  memcpy(Char5,c5,8);
  memcpy(Char6,c6,8);
  memcpy(Char7,c7,8);
  AtualizaLCD();

  DesenhaOlhos();

  lcd.setCursor(l+4,0); //X0 00
  lcd.write(byte(6));

  lcd.setCursor(l+5,0); //0X 00
  lcd.write(byte(5));

  lcd.setCursor(l+4,1); //00 X0
  lcd.write(byte(0));

  lcd.setCursor(l+5,1); //00 0X
  lcd.write(byte(7));
}

void Raiva()
{
  Padrao();

  uint8_t c5[8] = {0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x01};
  uint8_t c6[8] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10};

  memcpy(Char5,c5,8);
  memcpy(Char6,c6,8);
  AtualizaLCD();

  DesenhaOlhos();

  lcd.setCursor(l+1,0); //0X 00
  lcd.write(byte(5));

  lcd.setCursor(l+4,0); //0X 00
  lcd.write(byte(6));
}

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  Abertos();
  delay(2000);

  OlhandoEsq();
  delay(1000);

  OlhandoDir();
  delay(1000);

  Raiva();
  delay(1000);

  OlhandoEsq();
  delay(1000);

  OlhandoDir();
  delay(1000);

  PiscandoDir();
  delay(1000);
}
