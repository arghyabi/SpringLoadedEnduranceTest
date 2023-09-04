#ifndef EEPROM_CONTROL_H
#define EEPROM_CONTROL_H

#include <EEPROM.h>

void eepromWrite(int address, long value);
long eepromRead(int address);

#endif
