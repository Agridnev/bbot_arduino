#ifndef DRIVECONTROLLER_H
#define DRIVECONTROLLER_H

#include "motorcontroller.h"

class DriveController
{
public:
    struct Parameters
    {
        float linearK;
        float angularK;
    };

    struct Velocity
    {
        short int linear;
        short int angular;
    };

    DriveController(MotorController &mcFL, MotorController &mcFR, MotorController &mcRL, MotorController &mcRR, const Parameters &parameters);
    bool getEnabled() const;
    void setEnabled(bool enabled);
    Velocity getVelocity() const;
    void setVelocity(const Velocity &velocity);
    void update();

private:
    MotorController &mcFL;
    MotorController &mcFR;
    MotorController &mcRL;
    MotorController &mcRR;
    const Parameters parameters;
    bool enabled;
    Velocity velocity;
};

#endif
