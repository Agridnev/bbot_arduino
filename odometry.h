#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "encoder.h"

class Odometry
{
public:
    struct Parameters
    {
        float linearK;
        float angularK;
        short int hz;
    };

    struct Data
    {
        long int x;
        long int y;
        short int th;
        short int linear;
        short int angular;
    };

    Odometry(const Encoder &encoderFL, const Encoder &encoderFR, const Encoder &encoderRL, const Encoder &encoderRR, const Parameters &parameters);
    Data getData() const;
    void reset();
    void update();

private:
    const Encoder &encoderFL;
    const Encoder &encoderFR;
    const Encoder &encoderRL;
    const Encoder &encoderRR;
    const Parameters parameters;
    Data data;
    float fX;
    float fY;
    float fTh;
};

#endif
