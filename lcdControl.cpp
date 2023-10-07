#include <uRTCLib.h>
#include <LiquidCrystal_I2C.h>

#include "lcdControl.h"
#include "pinDescription.h"
#include "common.h"
#include "extra.h"

void PrintBlank(LiquidCrystal_I2C lcd, int count)
{
    switch(count)
    {
        case 1:
            lcd.print(" ");
            break;
        case 2:
            lcd.print("  ");
            break;
        case 3:
            lcd.print("   ");
            break;
        case 4:
            lcd.print("    ");
            break;
        case 5:
            lcd.print("     ");
            break;
        case 6:
            lcd.print("      ");
            break;
        case 7:
            lcd.print("       ");
            break;
        case 8:
            lcd.print("        ");
            break;
        case 9:
            lcd.print("         ");
            break;
        case 10:
            lcd.print("          ");
            break;
        case 11:
            lcd.print("           ");
            break;
        case 12:
            lcd.print("            ");
            break;
        case 13:
            lcd.print("             ");
            break;
        case 14:
            lcd.print("              ");
            break;
        case 15:
            lcd.print("               ");
            break;
        case 16:
            lcd.print("                ");
            break;
        case 17:
            lcd.print("                 ");
            break;
        case 18:
            lcd.print("                  ");
            break;
        case 19:
            lcd.print("                   ");
            break;
        case 20:
            lcd.print("                    ");
            break;
        default:
            lcd.print("");
            break;
    }
}

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

void PrintCount(LiquidCrystal_I2C lcd, int row, long int Count)
{
    int CountLen = numDigits(Count);
    lcd.setCursor(0, row);
    lcd.print("Count: ");
    lcd.setCursor(8, row);
    lcd.print(Count);
    lcd.setCursor(8 + CountLen, row);
    PrintBlank(lcd, LCD_MODULE_NO_OF_COLUMN - (7 + CountLen));
}
