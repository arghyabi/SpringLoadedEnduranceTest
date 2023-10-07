#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>
#include <uRTCLib.h>
#include <EEPROM.h>

#include "pinDescription.h"
#include "common.h"
#include "lcdControl.h"
#include "eepromControl.h"

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
uRTCLib rtc(RTC_MODULE_ADDRESS);

long int cycleCounter = 0;
int cycleIndexPos = 0;
bool cycleIndexPosMiddle = false;
bool isEepromReadNeed = true;

int currentPosition;
int previousPosition;


void setup()
{
    pinMode(ON_BOARD_LED_PIN, OUTPUT);
    URTCLIB_WIRE.begin();
    lcd.begin(LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
    lcd.setBacklight(HIGH);

    // rtc.set(0, 30, 9, 7, 15, 7, 23);
    // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
    pinMode(MICRO_SWITCH_S1_NC_PIN, INPUT);
    pinMode(MICRO_SWITCH_S1_NO_PIN, INPUT);
    pinMode(MICRO_SWITCH_S2_NC_PIN, INPUT);
    pinMode(MICRO_SWITCH_S2_NO_PIN, INPUT);

    pinMode(POWER_LINE_DETECT_PIN, INPUT);

    pinMode(ON_BOARD_LED_PIN, OUTPUT);

    if(digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        previousPosition = POSITION_LEFT;
        cycleIndexPos = POSITION_LEFT;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        previousPosition = POSITION_MIDDLE;
        cycleIndexPos = POSITION_MIDDLE;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        previousPosition = POSITION_RIGHT;
        cycleIndexPos = POSITION_RIGHT;
    }

    lcd.setCursor(0, ROW_NO_2);
    lcd.print("Count: ");
    lcd.setCursor(8, ROW_NO_2);
    lcd.print(cycleCounter);

    digitalWrite(ON_BOARD_LED_PIN, LOW);
}

void loop()
{
    rtc.refresh();
    PrintCurrentTime(lcd, rtc, ROW_NO_0);

    if(digitalRead(POWER_LINE_DETECT_PIN) == LOW)
    {
        lcd.setCursor(0, ROW_NO_3);
        lcd.print("Power Down");

        if(!isEepromReadNeed)
        {
            eepromWrite(EEPROM_COUNTER_SAVE_ADDRESS, cycleCounter);
            isEepromReadNeed = true;
        }
        return;
    }
    else
    {
        if(isEepromReadNeed)
        {
            cycleCounter = eepromRead(EEPROM_COUNTER_SAVE_ADDRESS);
            lcd.setCursor(0, ROW_NO_3);
            lcd.print("           ");
            isEepromReadNeed = false;
        }
    }

    if(digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        currentPosition = POSITION_LEFT;
        lcd.setCursor(0, ROW_NO_1);
        lcd.print("Position Left  ");
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        currentPosition = POSITION_MIDDLE;
        lcd.setCursor(0, ROW_NO_1);
        lcd.print("Position Middle");
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        currentPosition = POSITION_RIGHT;
        lcd.setCursor(0, ROW_NO_1);
        lcd.print("Position Right ");
    }

    if (currentPosition != previousPosition)
    {
        switch(currentPosition)
        {
            case POSITION_LEFT:
            case POSITION_RIGHT:
                if (cycleIndexPos == currentPosition)
                {
                    cycleCounter++;
                }
                break;
            case POSITION_MIDDLE:
                if (cycleIndexPosMiddle && (cycleIndexPos == currentPosition))
                {
                    cycleCounter++;
                }
                cycleIndexPosMiddle = !cycleIndexPosMiddle;
                break;
            default:
                break;
        }
    }

    previousPosition = currentPosition;

    lcd.setCursor(0, ROW_NO_2);
    lcd.print("Count: ");
    lcd.setCursor(8,ROW_NO_2);
    lcd.print(cycleCounter);

    if(cycleCounter >= 7500000)
    {
        digitalWrite(ON_BOARD_LED_PIN, HIGH);
        cycleCounter = 0;
    }
}
