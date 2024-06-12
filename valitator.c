#include <LiquidCrystal.h>

// Configuración del LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin digital del boton
const int buttonPin = 8;

// Setup
void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

// Loop
void loop()
{
  if (digitalRead(buttonPin) == HIGH)
  {
    lcd.print("Boton presionado");
    digitalWrite(13, HIGH);
    delay(300);
    digitalWrite(13, LOW);
  }
}