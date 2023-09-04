#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"

void PrintCurrentTime(LiquidCrystal_I2C lcd, uRTCLib rtc, int row)
{

    lcd.setCursor(0, row);
    lcd.print("                    ");
    lcd.setCursor(0, row);
    lcd.print(
        String(rtc.year()) +
        "/" +
        String(rtc.month()) +
        "/" +
        String(rtc.day()) +
        " " +
        String(rtc.hour()) +
        ":" +
        String(rtc.minute()) +
        ":" +
        String(rtc.second())
        );
}
