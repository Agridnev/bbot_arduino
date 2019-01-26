#ifndef PERIOD_H
#define PERIOD_H

class Period
{
public:
    Period(unsigned long period);
    bool check();

private:
    const unsigned long period;
    unsigned long last;
};

#endif
