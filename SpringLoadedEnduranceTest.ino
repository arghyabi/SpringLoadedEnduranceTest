
#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>
#include <uRTCLib.h>


#include "pinDescription.h"

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
uRTCLib rtc(RTC_MODULE_ADDRESS);

void setup()
{
    pinMode(ON_BOARD_LED_PIN, OUTPUT);
    URTCLIB_WIRE.begin();
    lcd.begin(LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
    lcd.setBacklight(HIGH);
    lcd.print("Hello, World!");

    // rtc.set(0, 30, 9, 7, 15, 7, 23);
    // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
}

void loop()
{
    rtc.refresh();
    digitalWrite(ON_BOARD_LED_PIN,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Good Day  ");
    delay(1000);
    digitalWrite(ON_BOARD_LED_PIN,LOW);
    lcd.setCursor(0,1);
    lcd.print("Good Night");
    delay(1000);

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
