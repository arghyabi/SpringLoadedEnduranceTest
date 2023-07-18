#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row, int offset)
{
    lcd.setCursor(offset + 0, row);
    lcd.print(rtc.year());
    lcd.setCursor(offset + 2, row);
    lcd.print("/");
    lcd.setCursor(offset + 3, row);
    lcd.print(rtc.month());
    lcd.print("/");
    lcd.setCursor(offset + 5, row);
    lcd.print(rtc.day());

    lcd.setCursor(offset + 8, row);
    lcd.print(rtc.hour());
    lcd.setCursor(offset + 10, row);
    lcd.print(':');
    lcd.setCursor(offset + 11, row);
    lcd.print(rtc.minute());
    lcd.setCursor(offset + 13, row);
    lcd.print(':');
    lcd.setCursor(offset + 14, row);
    lcd.println(rtc.second());
    lcd.setCursor(offset + 16, row);
    lcd.print('    ');
}
