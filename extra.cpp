#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

int numDigits(int val)
{
    char str[20];

    sprintf(str,"%d",abs(val));
    return(strlen(str));
}
