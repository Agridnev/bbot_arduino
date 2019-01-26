#include "motorcontroller.h"

MotorController::MotorController(Motor &motor, const Encoder &encoder, const Parameters &parameters) : motor(motor), encoder(encoder), parameters(parameters), enabled(false), targetEI(0), thCounter(0)
{
}

bool MotorController::getEnabled() const
{
    return enabled;
}

void MotorController::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

short int MotorController::getTargetEI() const
{
    return targetEI;
}

void MotorController::setTargetEI(short int targetEI)
{
    this->targetEI = targetEI;
}

void MotorController::update()
{
    // If motor is not enabled, stop it
    if (!enabled)
    {
        motor.setNextPWM(0);
        return;
    }
    // If motor is enabled, check threshold and calculate new PWM
    short int currentPWM = motor.getCurrentPWM();
    int currentEI = encoder.getValue();
    // If motor is powered with PWM more than thPWM and rotating in corresponding direction with speed less than thEI, activate threshold
    if (currentPWM > parameters.thPWM && currentEI < parameters.thEI || currentPWM < -parameters.thPWM && currentEI > -parameters.thEI)
    {
        ++thCounter;
        if (thCounter >= parameters.thN) // If threshold is active more than thN times in a row, disable motor
        {
            thCounter = 0;
            enabled = false;
            motor.setNextPWM(0);
            return;
        }
    }
    else
    {
        thCounter = 0;
    }
    // If motor needs to stop or change rotation direction, stop it
    if (targetEI == 0 || targetEI > 0 && currentEI < 0 || targetEI < 0 && currentEI > 0)
    {
        motor.setNextPWM(0);
        return;
    }
    // Calculate next PWM
    short int dPWM = (targetEI - currentEI) * parameters.k;
    short int nextPWM = currentPWM + dPWM;
    // Clamp PWM
    if (nextPWM > 255)
    {
        nextPWM = 255;
    }
    if (nextPWM < -255)
    {
        nextPWM = -255;
    }
    // If next PWM is opposite to rotation, stop motor
    if (nextPWM > 0 && currentEI < 0)
    {
        nextPWM = 0;
    }
    if (nextPWM < 0 && currentEI > 0)
    {
        nextPWM = 0;
    }
    // Set next PWM
    motor.setNextPWM(nextPWM);
}
