#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int i=0;

LiquidCrystal_I2C lcd(0x27,16,2);

uint8_t customChar[] =
{
  0x0e,
  0x11,
  0x19,
  0x1d,
  0x1d,
  0x19,
  0x11,
  0x0e
};

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Num:");
  lcd.setCursor(0,1);
  lcd.print("Nu^:");
}

void loop()
{
  lcd.setCursor(4,0);
  lcd.print(i);

  lcd.createChar(0, customChar);   // cria o caractere na posição 0
  lcd.setCursor(15,0);              // coluna 1, linha 0
  lcd.write(byte(0));

  lcd.setCursor(4,1);
  lcd.print(i*i);

  delay(1000);
  i++;
}