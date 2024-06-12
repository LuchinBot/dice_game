#include <LiquidCrystal.h>

// Configuración del LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin digital del boton
const int buttonPin = 8;

// Variables de juego
int currentPlayer = 0;
int playerScores[2] = {0, 0};
int currentTurnScore = 0;
bool buttonPressed = false;
bool firstRollWasOne = false;

// Setup
void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Juego de Dados iniciado");
  resetGame();
}

// Loop
void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    if (!buttonPressed)
    {
      buttonPressed = true;
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
      delay(50);
      playTurn();
    }
  }
  else
  {
    buttonPressed = false;
  }
}

// Funciones
void playTurn()
{
  int roll = rollDice();
  Serial.print("Jugador ");
  Serial.print(currentPlayer + 1);
  Serial.print(" tira: ");
  Serial.println(roll);

  if (roll == 1)
  {
    if (firstRollWasOne)
    {
      Serial.println("Sacas 1 otra vez! Pierdes el turno.");
      currentTurnScore = 0;
      firstRollWasOne = false;
      endTurn();
    }
    else
    {
      Serial.println("Sacas 1! Vuelves a tirar.");
      firstRollWasOne = true;
    }
  }
  else
  {
    currentTurnScore += roll;
    playerScores[currentPlayer] += currentTurnScore;
    currentTurnScore = 0;
    firstRollWasOne = false;
    endTurn();
  }
  updateLCD();
}

void endTurn()
{
  if (playerScores[currentPlayer] >= 50)
  {
    Serial.print("Jugador ");
    Serial.print(currentPlayer + 1);
    Serial.println(" gana el juego!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Jugador ");
    lcd.print(currentPlayer + 1);
    lcd.setCursor(0, 1);
    lcd.print("gana con ");
    lcd.print(playerScores[currentPlayer]);
    while (true)
      ; // Fin del juego
  }
  currentPlayer = (currentPlayer + 1) % 2;
  updateLCD();
}

int rollDice()
{
  return random(1, 7);
}

void updateLCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("J1: ");
  lcd.print(playerScores[0]);
  lcd.print(" J2: ");
  lcd.print(playerScores[1]);
  lcd.setCursor(0, 1);
  lcd.print("Turno: J");
  lcd.print(currentPlayer + 1);
}

void resetGame()
{
  currentPlayer = 0;
  playerScores[0] = 0;
  playerScores[1] = 0;
  currentTurnScore = 0;
  firstRollWasOne = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Juego de Dados");
  delay(2000);
  updateLCD();
}
