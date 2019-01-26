#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    Motor(unsigned char pinPWM, unsigned char pinENA, unsigned char pinENB);
    short int getCurrentPWM() const;
    short int getNextPWM() const;
    void setNextPWM(short int nextPWM);
    void apply();

private:
    const unsigned char pinPWM;
    const unsigned char pinENA;
    const unsigned char pinENB;
    short int currentPWM;
    short int nextPWM;
};

#endif
