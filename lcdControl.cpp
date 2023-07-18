#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row, int offset)
{
    lcd.setCursor(0,3);
    lcd.print(rtc.year());
    lcd.setCursor(2,3);
    lcd.print("/");
    lcd.setCursor(3,3);
    lcd.print(rtc.month());
    lcd.print("/");
    lcd.setCursor(5,3);
    lcd.print(rtc.day());

    lcd.setCursor(8,3);
    lcd.print(rtc.hour());
    lcd.setCursor(10,3);
    lcd.print(':');
    lcd.setCursor(11,3);
    lcd.print(rtc.minute());
    lcd.setCursor(13,3);
    lcd.print(':');
    lcd.setCursor(14,3);
    lcd.println(rtc.second());
}