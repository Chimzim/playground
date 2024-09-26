#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DHT.h>
#include <gardenDisplay.h>
#include <DHT_U.h>

gardenDisplay::gardenDisplay(int cols, int rows){
    LiquidCrystal_I2C lcd(0x27, cols, rows);
    lcd.begin();
    lcd.clear();
}

void gardenDisplay::turnDisplayOff(){
  LiquidCrystal_I2C lcd(0x27, SCREEN_LENGTH, SCREEN_HEIGHT);
  lcd.begin();
  lcd.clear();
  lcd.noDisplay();
}

void gardenDisplay::turnDisplayOn(){
  LiquidCrystal_I2C lcd(0x27, SCREEN_LENGTH, SCREEN_HEIGHT);
  lcd.begin();
  lcd.clear();
  lcd.display();
}

void gardenDisplay::printCollectionTime(String plantCollectionTime){
  LiquidCrystal_I2C lcd(0x27, SCREEN_LENGTH, SCREEN_HEIGHT);
  lcd.begin();
  lcd.clear();
  lcd.print(plantCollectionTime);
  delay(5000);
}

void gardenDisplay::printCollectedData(String currentData){
  LiquidCrystal_I2C lcd(0x27, SCREEN_LENGTH, SCREEN_HEIGHT);
  lcd.begin();
  lcd.clear();
  
  int len = currentData.length();
  int i = 0;
  String topLine = "";
  String bottomLine = "";
  int subStringIndex[3];
  int indexCounter = 0;
  bool endOfFirstLine = false;
  for(i = 0; i < len; i++){
    if(endOfFirstLine == false){
      if(currentData.charAt(i) != '\n'){
        topLine += currentData.charAt(i);
      }else{
        endOfFirstLine = true;
      }
    }else {
      if(currentData.charAt(i) == '\n'){
        subStringIndex[indexCounter++] = i;
      }else {
        bottomLine += currentData.charAt(i);
      }
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(topLine);
  lcd.setCursor(0,1);
  String movingBanner = "";
  i = 0;
  while(movingBanner.substring(movingBanner.length()-1) != currentData.substring(len-1)){
    movingBanner = bottomLine.substring(i, 16+i);
    i += 1;
    lcd.print(movingBanner);
    delay(1500);
  }
}

void gardenDisplay::printToDisplay(String text) {
  LiquidCrystal_I2C lcd(0x27, SCREEN_LENGTH, SCREEN_HEIGHT);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text);
}
