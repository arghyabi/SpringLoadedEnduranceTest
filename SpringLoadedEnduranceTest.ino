
#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>
#include <uRTCLib.h>
#include <EEPROM.h>


#include "pinDescription.h"
#include "lcdControl.h"
#include "eepromControl.h"

#define MOVE_LEFT(POS)  POS++
#define MOVE_RIGHT(POS) POS--
#define MOVEMENT_DETECTION(oldPos, newPos) oldPos - newPos
#define MOVEMENT_LEFT   1
#define MOVEMENT_RIGHT -1

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
uRTCLib rtc(RTC_MODULE_ADDRESS);
int sequence = -1;
int cycleIndex = 0;
long int cycleCounter = 0;

int cycleIndexPos = 0;
bool cycleIndexPosMiddle = false;
bool middlePosCycleComplete = false;
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
        cycleIndexPosMiddle = true;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        previousPosition = POSITION_RIGHT;
        cycleIndexPos = POSITION_RIGHT;
    }

    lcd.setCursor(0,2);
    lcd.print("Count: ");
    lcd.setCursor(8,2);
    lcd.print(cycleCounter);

    digitalWrite(ON_BOARD_LED_PIN, LOW);
}

void loop()
{
    rtc.refresh();
    PrintCurrentTime(lcd, rtc, 0);

    if(digitalRead(POWER_LINE_DETECT_PIN) == LOW)
    {
        lcd.setCursor(0,3);
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
            lcd.setCursor(0,3);
            lcd.print("           ");
            isEepromReadNeed = false;
        }
    }

    if(digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        currentPosition = POSITION_LEFT;
        lcd.setCursor(0,1);
        lcd.print("Position Left  ");
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        currentPosition = POSITION_MIDDLE;
        lcd.setCursor(0,1);
        lcd.print("Position Middle");
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        currentPosition = POSITION_RIGHT;
        lcd.setCursor(0,1);
        lcd.print("Position Right ");
    }

    cycleIndexPos = currentPosition;
    switch (MOVEMENT_DETECTION(previousPosition, currentPosition))
    {
    case MOVEMENT_LEFT:
        MOVE_LEFT(previousPosition);
        if(previousPosition == cycleIndexPos)
        {
            if(cycleIndexPosMiddle)
            {
                if(middlePosCycleComplete)
                {
                    cycleCounter++;
                    middlePosCycleComplete = false;
                }
                else
                {
                    middlePosCycleComplete = true;
                }
            }
            else
            {
                cycleCounter++;
            }
        }
        break;

    case MOVEMENT_RIGHT:
        MOVE_RIGHT(previousPosition);
        if(previousPosition == cycleIndexPos)
        {
            if(cycleIndexPosMiddle)
            {
                if(middlePosCycleComplete)
                {
                    cycleCounter++;
                    middlePosCycleComplete = false;
                }
                else
                {
                    middlePosCycleComplete = true;
                }
            }
            else
            {
                cycleCounter++;
            }
        }
        break;

    default:
        break;
    }
    previousPosition = currentPosition;

    lcd.setCursor(0,2);
    lcd.print("Count: ");
    lcd.setCursor(8,2);
    lcd.print(cycleCounter);

    if(cycleCounter >= 7500000)
    {
        digitalWrite(ON_BOARD_LED_PIN, HIGH);
        cycleCounter = 0;
    }
}
