#ifndef GARDENDISPLAY_H
#define GARDENDISPLAY_H
#define SCREEN_LENGTH 16
#define SCREEN_HEIGHT 2


#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>


class gardenDisplay{
    private:
    const String monthsArr[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    String formatMonth(int month);
    void turnDisplayOff();
    void turnDisplayOn();

    public:
    gardenDisplay(int cols, int rows);
    void printCollectionTime(String plantCollectionTime);
    void printCollectedData(String currentData);
    void printToDisplay(String text);

};
#endif