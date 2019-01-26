#include <Arduino.h>

#include "motor.h"

Motor::Motor(unsigned char pinPWM, unsigned char pinENA, unsigned char pinENB) : pinPWM(pinPWM), pinENA(pinENA), pinENB(pinENB), currentPWM(currentPWM), nextPWM(nextPWM)
{
}

short int Motor::getCurrentPWM() const
{
    return currentPWM;
}

short int Motor::getNextPWM() const
{
    return nextPWM;
}

void Motor::setNextPWM(short int nextPWM)
{
    if (nextPWM > 255)
        nextPWM = 255;
    if (nextPWM < -255)
        nextPWM = -255;
    this->nextPWM = nextPWM;
}

void Motor::apply()
{
    currentPWM = nextPWM;
    digitalWrite(pinENA, (currentPWM > 0));
    digitalWrite(pinENB, (currentPWM < 0));
    analogWrite(pinPWM, abs(currentPWM));
}
