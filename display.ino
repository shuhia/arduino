// UTILITY FUNCTIONS
// Add whitespace to text
String addWhiteSpace(String text, int length)
{
  for (int i = 0; i < length; i++)
  {
    text += " ";
  }

  return text;
}

String formatText(String text)
{
  return addWhiteSpace(text, 6);
}

/*
Arduino 2x16 LCD - Detect Buttons
modified on 18 Feb 2019
by Saeed Hosseini @ Electropeak
https://electropeak.com/learn/
*/
#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;

// Available digital output
const int pin_d2 = 2;
const int pin_d3 = 3;

LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

const int DISPLAY_MAX_LENGTH = 16;

String menuItems[6] = {"0", "1", "2", "3", "3", "4"};

int selectedIndex = 0;
bool isButtonDown = false;

void initDisplay()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Alex On");

  lcd.setCursor(0, 1);
  lcd.print("Select item: ");
  lcd.print(menuItems[selectedIndex]);
}

void clearDisplayRow(int row)
{
  String emptySpaceTemplate = "";
  emptySpaceTemplate = addWhiteSpace(emptySpaceTemplate, DISPLAY_MAX_LENGTH);
  lcd.setCursor(0, row);
  lcd.print(emptySpaceTemplate);
}

void updateDisplayRow(int row)
{
  if (row == 0)
  {
    clearDisplayRow(0);
    lcd.setCursor(0, 0);
    lcd.print("Alex On");
  }
  if (row == 1)
  {
    clearDisplayRow(1);
    lcd.setCursor(0, 1);
    lcd.print("Select item: ");
    lcd.print(selectedIndex);
  }
}

void initPins()
{
  pinMode(pin_d2, OUTPUT);
  pinMode(pin_d3, OUTPUT);
}

void setup()
{
  initDisplay();
  initPins();
}

// determine input
void onInput(int x)
{

  lcd.setCursor(10, 1);

  if (x == 1023)
  {
    isButtonDown = false;
    return;
  }

  if (!isButtonDown)
  {
    isButtonDown = true;
    if (x < 60)
    {
      handleRightButtonClick("Right ");
    }
    else if (x < 200)
    {
      handleUpButtonClick("Up ");
    }
    else if (x < 400)
    {
      handleDownButtonClick("Down ");
    }
    else if (x < 600)
    {
      handleLeftButtonClick("Left ");
    }
    else if (x < 800)
    {
      handleSelectButtonClick("Select");
    }
  }
}

// Input handlers
void handleUpButtonClick(String args)
{
  lcd.print("Top");
  selectedIndex++;
  updateDisplayRow(1);
}

void handleDownButtonClick(String args)
{
  lcd.print("Bottom");
  selectedIndex--;
  updateDisplayRow(1);
}

void handleLeftButtonClick(String args)
{
  lcd.print("Left");
}

void handleRightButtonClick(String args)
{
  lcd.print("Right");
}

void handleSelectButtonClick(String args)
{
  lcd.print("Select");
}

void handleResetButtonClick()
{
  lcd.print("Reset ");
}

void loop()
{
  int x;
  // Check for input
  x = analogRead(0);
  onInput(x);
}
