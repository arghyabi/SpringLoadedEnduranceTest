
#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>


#include "pinDescription.h"

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);

void setup()
{
    pinMode(ON_BOARD_LED_PIN, OUTPUT);
    lcd.begin(LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
    lcd.setBacklight(HIGH);
    lcd.print("Hello, World!");
}

void loop()
{
    digitalWrite(ON_BOARD_LED_PIN,HIGH);
    lcd.setCursor(0,1);
    lcd.print("Good Day  ");
    delay(1000);
    digitalWrite(ON_BOARD_LED_PIN,LOW);
    lcd.setCursor(0,1);
    lcd.print("Good Night");
    delay(1000);
}
