#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row, int offset)
{
    lcd.setCursor(0,2);
    lcd.print(rtc.year());
    lcd.setCursor(2,2);
    lcd.print("/");
    lcd.setCursor(3,2);
    lcd.print(rtc.month());
    lcd.print("/");
    lcd.setCursor(5,2);
    lcd.print(rtc.day());

    lcd.setCursor(8,2);
    lcd.print(rtc.hour());
    lcd.setCursor(10,2);
    lcd.print(':');
    lcd.setCursor(11,2);
    lcd.print(rtc.minute());
    lcd.setCursor(13,2);
    lcd.print(':');
    lcd.setCursor(14,2);
    lcd.println(rtc.second());
}