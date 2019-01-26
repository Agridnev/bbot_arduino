#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "motor.h"
#include "encoder.h"

class MotorController
{
public:
    struct Parameters
    {
        float k;
        short int thPWM;
        short int thEI;
        unsigned short thN;
    };

    MotorController(Motor &motor, const Encoder &encoder, const Parameters &parameters);
    bool getEnabled() const;
    void setEnabled(bool enabled);
    short int getTargetEI() const;
    void setTargetEI(short int targetEI);
    void update();

private:
    Motor &motor;
    const Encoder &encoder;
    const Parameters parameters;
    bool enabled;
    short int targetEI;
    unsigned short int thCounter;
};

#endif
