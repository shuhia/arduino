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
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
void setup() {
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Electropeak.com");
 lcd.setCursor(0,1);
 lcd.print("Press Key:");
}

// determine input
void onInput(int x){
 lcd.setCursor(10,1);
 if (x < 60) {
   handleRightButtonClick("Right ");
 }
 else if (x < 200) {
   handleUpButtonClick("Up ");
 }
 else if (x < 400){
   handleDownButtonClick("Down ");
 }
 else if (x < 600){
   handleLeftButtonClick("Left ");
 }
 else if (x < 800){
   handleSelectButtonClick("Select");
 }

}

// Add whitespace to text 
String fillWithSpace(String text, int preferedLength){
  for(int i = text.length(); i<=preferedLength; i++){
    text += " ";
  }

  return text;
}

String formatText(String text){
  return fillWithSpace(text, 6);
}

// Input handlers
void handleUpButtonClick(String args){
     lcd.print(formatText("Top    "));
}

void handleDownButtonClick(String args){
     lcd.print(formatText("Bottom "));
}

void handleLeftButtonClick(String args){
     lcd.print(formatText("Left "));
}

void handleRightButtonClick(String args){
     lcd.print(formatText("Right "));
}

void handleSelectButtonClick(String args){
     lcd.print(formatText("Select "));
}





void loop() {
 int x;
 // Check for input 
 x = analogRead (0);
  onInput(x);
 
} 

