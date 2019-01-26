#ifndef BATTERY_H
#define BATTERY_H

class Battery
{
public:
    struct Parameters
    {
        float k;
        float b;
    };

    Battery(unsigned char pin, const Parameters &parameters);
    void measure();
    unsigned char getValue() const;

private:
    const unsigned char pin;
    const Parameters parameters;
    unsigned char value;
};

#endif
