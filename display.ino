
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
#pragma region Liquid Crystal
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

#pragma endregion

const int DISPLAY_MAX_LENGTH = 16;
int selectedButton = 0;

#pragma region Menu
int selectedItem = 0;
String menuItems[6] = {"0", "1", "2", "3", "3", "4"};
void selectNextItem()
{
  selectedItem++;
}
void selectPreviousItem()
{
  selectedItem--;
}
#pragma endregion

#pragma region Display

void initDisplay()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Alex On");

  lcd.setCursor(0, 1);
  lcd.print("Select item: ");
  lcd.print(menuItems[selectedItem]);
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
    lcd.print(selectedItem);
  }
}

void printOnDisplayRow(int row, String text)
{
  clearDisplayRow(row);
  lcd.setCursor(0, row);
  lcd.print(text);
}

// Prints text selected key on row
void printSelectedKeyOnFirstRow(String key)
{
  printOnDisplayRow(0, "key: " + key);
}

#pragma endregion

#pragma region initalize
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

#pragma endregion
// determineDisplayButton
// Function returns an integer value based on what button is pressed
#pragma region Buttons
#define DISPLAY_BUTTON_UP 0
#define DISPLAY_BUTTON_DOWN 1
#define DISPLAY_BUTTON_LEFT 2
#define DISPLAY_BUTTON_RIGHT 4
#define DISPLAY_BUTTON_SELECT 5
bool isButtonDown = false;

int determineDisplayButton(int value)
{
  isButtonDown = true;
  if (value < 60)
  {
    return DISPLAY_BUTTON_RIGHT;
  }
  else if (value < 200)
  {
    return DISPLAY_BUTTON_UP;
  }
  else if (value < 400)
  {
    return DISPLAY_BUTTON_DOWN;
  }
  else if (value < 600)
  {
    return DISPLAY_BUTTON_LEFT;
  }
  else if (value < 800)
  {
    return DISPLAY_BUTTON_SELECT;
  }

  return 0;
}

void handleButtonPress(int key)
{
  selectedButton = key;
  switch (key)
  {
  case DISPLAY_BUTTON_UP:
    handleUpButtonClick("Up ");
    break;
  case DISPLAY_BUTTON_DOWN:
    handleDownButtonClick("Down ");
    break;
  case DISPLAY_BUTTON_LEFT:
    handleLeftButtonClick("Left ");
    break;
  case DISPLAY_BUTTON_RIGHT:
    handleRightButtonClick("Right ");
    break;
  case DISPLAY_BUTTON_SELECT:
    handleSelectButtonClick("Select");
    break;
  default:
    break;
  }
}

bool onButton(int value)
{
  // Check if button is down
  if (value == 1023)
  {
    isButtonDown = false;
    return false;
  }

  if (!isButtonDown)
  {
    isButtonDown = true;
    int key = determineDisplayButton(value);
    handleButtonPress(key);
    return true;
  }
}

// check for types of input
bool onInput(int value)
{
  if (onButton(value))
    return true;
  return false;
}

// Input handlers
void handleUpButtonClick(String args)
{
  printSelectedKeyOnFirstRow("Top");
  selectNextItem();
  updateDisplayRow(1);
}

void handleDownButtonClick(String args)
{
  printSelectedKeyOnFirstRow("Bottom");
  selectPreviousItem();
  updateDisplayRow(1);
}

void handleLeftButtonClick(String args)
{
  printSelectedKeyOnFirstRow("Left");
}

void handleRightButtonClick(String args)
{
  printSelectedKeyOnFirstRow("Right");
}

void handleSelectButtonClick(String args)
{
  printSelectedKeyOnFirstRow("Select");
}

void handleResetButtonClick()
{
  printSelectedKeyOnFirstRow("Reset ");
}

#pragma endregion
void loop()
{
  int x;
  // Check for input
  x = analogRead(0);
  Serial.println(x);

  // Filter input

  onInput(x);
}
