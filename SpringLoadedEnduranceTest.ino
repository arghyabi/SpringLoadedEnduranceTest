
#include <Arduino.h>
#include <Wire.h> // For I2C
#include <LiquidCrystal_I2C.h>
#include <uRTCLib.h>
#include <EEPROM.h>


#include "pinDescription.h"
#include "lcdControl.h"

#define MOVE_LEFT(POS) POS++
#define MOVE_RIGHT(POS) POS--
#define MOVEMENT_DETECTION(oldPos, newPos) oldPos - newPos
#define MOVEMENT_LEFT 1
#define MOVEMENT_RIGHT -1

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LiquidCrystal_I2C lcd(LCD_MODULE_ADDRESS, LCD_MODULE_NO_OF_COLUMN, LCD_MODULE_NO_OF_ROW);
uRTCLib rtc(RTC_MODULE_ADDRESS);
int sequence = -1;
int cycleIndex = 0;
long int cycleCounter = 0;

int cycleIndexPos = 0;
long cycleCounterD = 0;
bool cycleIndexPosMiddle = false;
bool middlePosCycleComplete = false;

int currentPosition;
int previousPosition;

bool isEepromReadNeed = true;

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
        sequence = -1;
        cycleIndexPos = POSITION_LEFT;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        previousPosition = POSITION_MIDDLE;
        sequence = 0;
        cycleIndexPos = POSITION_MIDDLE;
        cycleIndexPosMiddle = true;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        previousPosition = POSITION_RIGHT;
        sequence = 1;
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

    if(digitalRead(POWER_LINE_DETECT_PIN) == LOW)
    {
        lcd.setCursor(0,3);
        lcd.print("Power Down;");

        if(!isEepromReadNeed)
        {
            EEPROM.write(EEPROM_COUNTER_SAVE_ADDRESS, cycleCounterD);
            isEepromReadNeed = true;
        }
        return;
    }
    else
    {
        if(isEepromReadNeed)
        {
            cycleCounterD = EEPROM.read(EEPROM_COUNTER_SAVE_ADDRESS);
            lcd.setCursor(0,3);
            lcd.print("           ");
            isEepromReadNeed = false;
        }
    }

    if(digitalRead(MICRO_SWITCH_S1_NO_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        // previousPosition = currentPosition;
        // currentPosition = POSITION_LEFT;
        // sequence++;
        currentPosition = POSITION_LEFT;
        lcd.setCursor(0,1);
        lcd.print("Position Left  ");
        cycleIndex++;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NC_PIN))
    {
        currentPosition = POSITION_MIDDLE;
        // sequence++;
        lcd.setCursor(0,1);
        lcd.print("Position Middle");
        cycleIndex++;
    }

    if(digitalRead(MICRO_SWITCH_S1_NC_PIN) && digitalRead(MICRO_SWITCH_S2_NO_PIN))
    {
        currentPosition = POSITION_RIGHT;
        // sequence = -1;
        lcd.setCursor(0,1);
        lcd.print("Position Right ");
        cycleIndex++;
    }

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
                    cycleCounterD++;
                    middlePosCycleComplete = false;
                }
                else
                {
                    middlePosCycleComplete = true;
                }
            }
            else
            {
                cycleCounterD++;
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
                    cycleCounterD++;
                    middlePosCycleComplete = false;
                }
                else
                {
                    middlePosCycleComplete = true;
                }
            }
            else
            {
                cycleCounterD++;
            }
        }
        break;

    default:
        break;
    }

    lcd.setCursor(0,2);
    lcd.print("Count: ");
    lcd.setCursor(8,2);
    lcd.print(cycleCounterD);

    if(cycleCounterD >= 7500000)
    {
        digitalWrite(ON_BOARD_LED_PIN, HIGH);
        cycleCounterD = 0;
    }


    // if(cycleIndex == 3)
    // {
    //     cycleIndex = 0;
    //     cycleCounter++;
    //     lcd.setCursor(0,2);
    //     lcd.print("Count: ");
    //     lcd.setCursor(8,2);
    //     lcd.print(cycleCounter);
    //     if(cycleCounter >= 7500000)
    //     {
    //          digitalWrite(ON_BOARD_LED_PIN, HIGH);
    //          cycleCounter = 0;
    //     }
    // }

    PrintCurrentTime(lcd, rtc, 0, 0);
}
