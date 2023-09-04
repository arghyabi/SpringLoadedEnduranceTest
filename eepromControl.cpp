#include "eepromControl.h"

void eepromWrite(int address, long value)
{
    EEPROM.write(address, (value & 0xFF));
    EEPROM.write(address + 1, ((value >> 8) & 0xFF));
    EEPROM.write(address + 2, ((value >> 16) & 0xFF));
}


long eepromRead(int address)
{
    long data = 0;
    data = EEPROM.read(address);
    data = ((EEPROM.read(address + 1)) << 8) | data;
    data = ((long)(EEPROM.read(address + 2)) << 16) | data;
    return data;
}
