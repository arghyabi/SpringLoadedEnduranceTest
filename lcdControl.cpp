#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"
#include "pinDescription.h"

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row)
{
    String dateData;

    dateData = String(rtc.year()) +
        "/" +
        String(rtc.month()) +
        "/" +
        String(rtc.day()) +
        " " +
        String(rtc.hour()) +
        ":" +
        String(rtc.minute()) +
        ":" +
        String(rtc.second());

    for(int i = dateData.length(); i < LCD_MODULE_NO_OF_COLUMN; i++)
    {
        dateData += " ";
    }

    lcd.setCursor(0, row);
    lcd.print(dateData);
}
