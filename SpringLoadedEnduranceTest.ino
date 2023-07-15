#include "pinDescription.h"

void setup()
{
    pinMode(ON_BOARD_LED_PIN, OUTPUT);
}

void loop()
{
    digitalWrite(ON_BOARD_LED_PIN,HIGH);
    delay(1000);
    digitalWrite(ON_BOARD_LED_PIN,LOW);
    delay(1000);
}
