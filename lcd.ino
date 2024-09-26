#include <DHT.h>
#include <DHT_U.h>

#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int wet = 239;
const int dry = 540;
const String monthsArr[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
boolean timeToCollect = true;
int lastCollectedTime = hour() - 1;

struct plant{
   float temperature;
   float humidityPercentage;
   int moistureLevel;
   int numMonth;
   int numYear;
   int numDay;
   int numHour;
   int numMins;
};

plant cilantroPlant[24];
plant pepperPlant[24]; 

void setup() {
  // put your setup code here, to run once:
lcd.begin();
dht.begin();
lcd.clear();
setTime(17,15,15,4,11,2022);
fillArrays();
}

void fillArrays() {
  int i = 0;
  for(i =0; i < 24; i++){
    pepperPlant[i] = {0.0, 0, 0, 10, 2022,0, 0, 0};
    cilantroPlant[i] = {0.0,0, 0, 10, 2022,0, 0, 0};
  }
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(timeToWater(analogRead(A0)) || timeToWater(analogRead(A1)) ){
//    lcd.clear();
//    String plantName = timeToWater(analogRead(A0)) ? "Pepper Plant" : "Cilantro Plant";
//    int moistureLevel = timeToWater(analogRead(A0)) ? analogRead(A0) : analogRead(A1);
//    lcd.setCursor(0,0);
//    lcd.print("Moisture Level: ");
//    lcd.print(moistureLevel);
//    lcd.setCursor(0,1);
//    lcd.print("Water ");
//    lcd.print(plantName);
//    delay(5000);
//  }
//  else if(hour() > 9 && hour() < 23) {
//    printOutput();
//    collectData(hour());
//  }else {
//    collectData(hour());
//   int i = 0;
//   for(i < 0; i < 24; i++){
//    printOutput(pepperPlant[i], "Pepper Plant", i);
//   }
//   i = 0;
//   for(i < 0; i < 24; i++){
//    printOutput(cilantroPlant[i], "Cilantro", i);
//   }
//    
//  }
  lcd.clear();
  collectData(hour());
  printOutput(pepperPlant[hour()], "pepper plant", hour());
 // printOutput(cilantroPlant[hour()], "cilantro", hour());
 if(pepperPlant[hour()].temperature || pepperPlant[hour()].humidityPercentage) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Couldn't read");
  lcd.setCursor(0,1);
  lcd.print("from dht");
 }
}

boolean timeToWater(int current) {
  if(current >= 520) {
    return true;
  }
  return false;
}

void printOutput(){
  int sensorValue = analogRead(A0);
  String movingBanner = "Cilantro Plant";
  lcd.clear();
  printTime();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(dht.readHumidity());
  lcd.print("%");
  lcd.setCursor(0,0);
  lcd.print(movingBanner);
  delay(5000);
  
  lcd.clear();
  printTime();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(dht.readTemperature(true));
  lcd.print(" F");
  lcd.setCursor(0,0);
  lcd.print(movingBanner);
delay(5000);

  sensorValue = analogRead(A1);
  movingBanner = "Pepper Plant";
  lcd.clear();
  printTime();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(dht.readHumidity());
  lcd.print("%");
  lcd.setCursor(0,0);
  lcd.print(movingBanner);
  delay(5000);
  
  lcd.clear();
  printTime();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(dht.readTemperature(true));
  lcd.print(" F");
  lcd.setCursor(0,0);
  lcd.print(movingBanner);
  delay(5000);
}

void printOutput(plant toPrint, String plantName, int pos) {
  lcd.clear();
  printTime(toPrint);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(plantName);
  if(plantName == "Cilantro") {
    lcd.print(" entry ");
  }else {
    lcd.print(" ");
  }
  lcd.print(pos);
  lcd.setCursor(0, 1); 
lcd.print("Moisture Level: ");
  lcd.print(toPrint.moistureLevel);
   delay(10000);  
  lcd.clear();
  printTime(toPrint);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(plantName);
  if(plantName == "Cilantro") {
    lcd.print(" entry ");
  }else {
    lcd.print(" ");
  }
  lcd.print(pos); 
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(toPrint.humidityPercentage);
  lcd.print("%");
  delay(10000);  
  lcd.clear();
  printTime(toPrint);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(plantName);
  if(plantName == "Cilantro") {
    lcd.print(" entry ");
  }else {
    lcd.print(" ");
  }
  lcd.print(pos); 
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(toPrint.temperature);
  lcd.print(" F");

  delay(10000);    
}

void collectData(int currentHour){
 // if(currentHour > lastCollectedTime) {
    int sensorValue = analogRead(A0);
    lastCollectedTime = hour();
    cilantroPlant[currentHour].humidityPercentage = dht.readHumidity();
    cilantroPlant[currentHour].moistureLevel = sensorValue;
    cilantroPlant[currentHour].numMonth = month();
    cilantroPlant[currentHour].numYear = year();
    cilantroPlant[currentHour].numDay = day();
    cilantroPlant[currentHour].numMins = minute();
    cilantroPlant[currentHour].numHour = hour();
    cilantroPlant[currentHour].temperature = dht.readTemperature(true);
    sensorValue = analogRead(A1);
    pepperPlant[currentHour].humidityPercentage = dht.readHumidity();
    pepperPlant[currentHour].moistureLevel = sensorValue;
    pepperPlant[currentHour].numMonth = month();
    pepperPlant[currentHour].numYear = year();
    pepperPlant[currentHour].numDay = day();
    pepperPlant[currentHour].numMins = minute();
    pepperPlant[currentHour].numHour = hour();
    pepperPlant[currentHour].temperature = dht.readTemperature(true);
 // }
}


void printTime(){
  lcd.print(day());
  lcd.print("-");
  lcd.print(formatMonth(month()));
  lcd.print("-");
  lcd.print(year());
  lcd.print(" ");
  lcd.setCursor(0,1);
  int hours = hour();
  String timeOfDay = " am";
  if(hours > 12) {
    lcd.print(hours - 12);
    timeOfDay = " pm";
  }else {
    lcd.print(hours);
  }
  lcd.print(":");
  int mins = minute();
  if(mins >= 10) {
    lcd.print(mins); 
    lcd.print(timeOfDay); 
  }else {
    lcd.print(0);
    lcd.print(mins);
    lcd.print(timeOfDay);
  }
  delay(5000);
}

void printTime(plant current){
  lcd.print(current.numDay);
  lcd.print("-");
  lcd.print(formatMonth(current.numMonth));
  lcd.print("-");
  lcd.print(current.numYear);
  lcd.print(" ");
  lcd.setCursor(0,1);
  int hours = current.numHour;
  String timeOfDay = " am";
  if(hours > 12) {
    lcd.print(hours - 12);
    timeOfDay = " pm";
  }else {
    lcd.print(hours);
  }
  lcd.print(":");
  int mins = current.numMins;
  if(mins >= 10) {
    lcd.print(mins); 
    lcd.print(timeOfDay); 
  }else {
    lcd.print(0);
    lcd.print(mins);
    lcd.print(timeOfDay);
  }
  delay(5000);
}

String formatMonth(int month) {
  return monthsArr[month-1];
}
