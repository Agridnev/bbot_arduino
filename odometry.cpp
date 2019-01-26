#include <math.h>

#include "odometry.h"

#define abs(x) ((x) < 0 ? -(x) : (x))
#define minabs(x, y) (abs(x) < abs(y) ? (x) : (y))

Odometry::Odometry(const Encoder &encoderFL, const Encoder &encoderFR, const Encoder &encoderRL, const Encoder &encoderRR, const Parameters &parameters) :
encoderFL(encoderFL), encoderFR(encoderFR), encoderRL(encoderRL), encoderRR(encoderRR), parameters(parameters), data{0, 0, 0}, fX(0.0f), fY(0.0f), fTh(0.0f)
{
}

Odometry::Data Odometry::getData() const
{
    return data;
}

void Odometry::reset()
{
    data = Data{0, 0, 0, 0, 0};
    fX = 0.0f;
    fY = 0.0f;
    fTh = 0.0f;
}

void Odometry::update()
{
    short int flEI = encoderFL.getValue();
    short int frEI = encoderFR.getValue();
    short int rlEI = encoderRL.getValue();
    short int rrEI = encoderRR.getValue();
    short int leftEI = minabs(flEI, rlEI);
    short int rightEI = minabs(frEI, rrEI);
    float dTh = (rightEI - leftEI) * parameters.angularK;
    fTh += dTh;
    while (fTh > M_PI)
    {
        fTh -= 2 * M_PI;
    }
    while (fTh <= -M_PI)
    {
        fTh += 2 * M_PI;
    }
    float dL = (rightEI + leftEI) * parameters.linearK;
    float dX = fX + dL * cos(fTh);
    float dY = fY + dL * sin(fTh);
    long int dXI = dX;
    long int dYI = dY;
    fX = dX - dXI;
    fY = dY - dYI;
    data = Data{data.x + dXI, data.y + dYI, (short int) (fTh * 180.0f / M_PI), (short int) (dL * parameters.hz), (short int) (dTh * parameters.hz * 180.0f / M_PI)};
}
