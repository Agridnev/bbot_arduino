#include <Arduino.h>

#include "period.h"

Period::Period(unsigned long period) : period(period)
{
}

bool Period::check()
{
    if (millis() - last >= period)
    {
        last = millis();
        return true;
    }
    return false;
}
