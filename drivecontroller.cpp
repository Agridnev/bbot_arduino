#include "drivecontroller.h"

DriveController::DriveController(MotorController &mcFL, MotorController &mcFR, MotorController &mcRL, MotorController &mcRR, const Parameters &parameters) :
    mcFL(mcFL), mcFR(mcFR), mcRL(mcRL), mcRR(mcRR), parameters(parameters), enabled(false), velocity{0, 0}
{
}

bool DriveController::getEnabled() const
{
    return enabled;
}

void DriveController::setEnabled(bool enabled)
{
    this->enabled = enabled;
    mcFL.setEnabled(enabled);
    mcFR.setEnabled(enabled);
    mcRL.setEnabled(enabled);
    mcRR.setEnabled(enabled);
}

DriveController::Velocity DriveController::getVelocity() const
{
    return velocity;
}

void DriveController::setVelocity(const Velocity &velocity)
{
    this->velocity = velocity;
    short int linearEI = velocity.linear * parameters.linearK;
    short int angularEI = velocity.angular * parameters.angularK;
    short int leftEI = linearEI - angularEI;
    short int rightEI = linearEI + angularEI;
    mcFL.setTargetEI(leftEI);
    mcFR.setTargetEI(rightEI);
    mcRL.setTargetEI(leftEI);
    mcRR.setTargetEI(rightEI);
}

void DriveController::update()
{
    mcFL.update();
    mcFR.update();
    mcRL.update();
    mcRR.update();
    if (!mcFL.getEnabled() || !mcFR.getEnabled() || !mcRL.getEnabled() || !mcRR.getEnabled())
    {
        setEnabled(false);
    }
}
