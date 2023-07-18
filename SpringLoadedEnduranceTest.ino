
#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>
#include <uRTCLib.h>


#include "pinDescription.h"
#include "lcdControl.h"

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
uRTCLib rtc(RTC_MODULE_ADDRESS);
int sequence = -1;

void setup()
{
    pinMode(ON_BOARD_LED_PIN, OUTPUT);
    URTCLIB_WIRE.begin();
    lcd.begin(LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
    lcd.setBacklight(HIGH);
    lcd.print("Hello, World!");

    // rtc.set(0, 30, 9, 7, 15, 7, 23);
    // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
    pinMode(MICRO_SWITCH_S1_NC_PIN, INPUT);
    pinMode(MICRO_SWITCH_S1_NO_PIN, INPUT);
    pinMode(MICRO_SWITCH_S2_NC_PIN, INPUT);
    pinMode(MICRO_SWITCH_S2_NO_PIN, INPUT);

    if(digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        lcd.setCursor(0,1);
        lcd.print("Init Position Left  ");
        sequence = -1;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        sequence = 0;
        lcd.setCursor(0,1);
        lcd.print("Init Position Middle");
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        sequence = 1;
        lcd.setCursor(0,1);
        lcd.print("Init Position Right ");
    }
}

void loop()
{
    rtc.refresh();
    if(sequence == -1 && digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        lcd.setCursor(0,2);
        lcd.print("Position Left  ");
        sequence++;
    }

    if(sequence == 0 && digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        sequence++;
        lcd.setCursor(0,2);
        lcd.print("Position Middle");
    }

    if(sequence == 1 && digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        sequence = -1;
        lcd.setCursor(0,2);
        lcd.print("Position Right ");
    }

    PrintCurrentTime(lcd, rtc, 3, 0);
}
