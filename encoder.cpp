#include <Arduino.h>

#include "encoder.h"

Encoder::Encoder(unsigned char pinCHA, unsigned char pinCHB) : pinCHA(pinCHA), pinCHB(pinCHB), counter(0), value(0)
{
}

void Encoder::interrupt()
{
    counter += (digitalRead(pinCHA) ^ digitalRead(pinCHB)) * 2 - 1;
}

void Encoder::fix()
{
    value = counter;
    counter = 0;
}

int Encoder::getValue() const
{
    return value;
}
