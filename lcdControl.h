#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row);
void PrintCount(LiquidCrystal_I2C lcd, int row, long int Count);

#endif
