#include "period.h"
#include "motor.h"
#include "encoder.h"
#include "motorcontroller.h"
#include "drivecontroller.h"
#include "odometry.h"
#include "battery.h"
#include "protocol.h"

const int PIN_BAT = 0; // ANALOG battery voltage measurement
const int PIN_PWM[4] = {2,  3,  4,  5};  // PWM for motors
const int PIN_ENA[4] = {23, 24, 27, 28}; // Enable motor in A direction
const int PIN_ENB[4] = {22, 25, 26, 29}; // Enable motor in B direction
const int PIN_CHA[4] = {31, 32, 35, 36}; // Encoder channel A
const int PIN_CHB[4] = {30, 33, 34, 37}; // Encoder channel B

Period period(50); // 20 Hz

Motor motorFL(PIN_PWM[0], PIN_ENA[0], PIN_ENB[0]);
Motor motorFR(PIN_PWM[1], PIN_ENA[1], PIN_ENB[1]);
Motor motorRL(PIN_PWM[2], PIN_ENA[2], PIN_ENB[2]);
Motor motorRR(PIN_PWM[3], PIN_ENA[3], PIN_ENB[3]);

Encoder encoderFL(PIN_CHA[0], PIN_CHB[0]);
Encoder encoderFR(PIN_CHA[1], PIN_CHB[1]);
Encoder encoderRL(PIN_CHA[2], PIN_CHB[2]);
Encoder encoderRR(PIN_CHA[3], PIN_CHB[3]);

void encoderInterruptFL() {
    encoderFL.interrupt();
}

void encoderInterruptFR() {
    encoderFR.interrupt();
}

void encoderInterruptRL() {
    encoderRL.interrupt();
}

void encoderInterruptRR() {
    encoderRR.interrupt();
}

MotorController::Parameters mcParameters = {0.5f, // float k            -- dPWM = k * errorEI
                                            127,  // short int thPWM    -- threshold PWM, min PWM condition
                                            10,   // short int thEI     -- threshold EI,  min EI condition
                                            5};   // unsigned short thN -- threshold N,   N times in a row condition

MotorController motorControllerFL(motorFL, encoderFL, mcParameters);
MotorController motorControllerFR(motorFR, encoderFR, mcParameters);
MotorController motorControllerRL(motorRL, encoderRL, mcParameters);
MotorController motorControllerRR(motorRR, encoderRR, mcParameters);

DriveController::Parameters dcParameters = {0.12f,  // float linearK
                                            0.35f}; // float angularK

DriveController::Velocity dcVelocity = {0, 0};

DriveController driveController(motorControllerFL, motorControllerFR, motorControllerRL, motorControllerRR, dcParameters);

Odometry::Parameters odometryParameters = {0.25f,   // float linearK
                                           0.0016f, // float angularK
                                           20};     // short int hz;

Odometry odometry(encoderFL, encoderFR, encoderRL, encoderRR, odometryParameters);

Battery::Parameters batteryParameters = {0.3639f, // float k
                                         5.678f}; // float b

Battery battery(PIN_BAT, batteryParameters);

void cbMotors(const Protocol::Motors &motors);
void cbVelocity(const Protocol::Velocity &velocity);

Protocol protocol(cbMotors, cbVelocity);

const unsigned int velocityTTLStart = 2;
unsigned int velocityTTL = 0;

void setup() {
    Serial.begin(115200);
    void (*const encoderInterrupts[4])() = {encoderInterruptFL, encoderInterruptFR, encoderInterruptRL, encoderInterruptRR};
    for (byte i = 0; i < 4; ++i)
    {
        pinMode(PIN_PWM[i], OUTPUT);
        pinMode(PIN_ENA[i], OUTPUT);
        pinMode(PIN_ENB[i], OUTPUT);
        pinMode(PIN_CHA[i], INPUT_PULLUP);
        pinMode(PIN_CHB[i], INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(PIN_CHA[i]), encoderInterrupts[i], CHANGE);
    }
}

void loop() {
    if (period.check())
    {
        encoderFL.fix();
        encoderFR.fix();
        encoderRL.fix();
        encoderRR.fix();
        odometry.update();
        Odometry::Data odata = odometry.getData();
        battery.measure();
        if (velocityTTL)
        {
            --velocityTTL;
        }
        else
        {
            driveController.setEnabled(0);
        }
        driveController.setVelocity(dcVelocity);
        driveController.update();
        motorFL.apply();
        motorFR.apply();
        motorRL.apply();
        motorRR.apply();
        protocol.send(Protocol::Data{odata.x, odata.y, odata.th, odata.linear, odata.angular, driveController.getEnabled(), battery.getValue()});
    }
    protocol.receive();
}

void cbMotors(const Protocol::Motors &motors)
{
    driveController.setEnabled(motors.enable);
}

void cbVelocity(const Protocol::Velocity &velocity)
{
    dcVelocity.linear = velocity.linear;
    dcVelocity.angular = velocity.angular;
    velocityTTL = velocityTTLStart;
}
