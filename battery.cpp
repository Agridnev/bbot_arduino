#include <Arduino.h>

#include "battery.h"

Battery::Battery(unsigned char pin, const Parameters &parameters) : pin(pin), parameters(parameters), value(value)
{
}

void Battery::measure()
{
    value = analogRead(pin) * parameters.k + parameters.b;
}

unsigned char Battery::getValue() const
{
    return value;
}
