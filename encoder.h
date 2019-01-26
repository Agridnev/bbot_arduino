#ifndef ENCODER_H
#define ENCODER_H

class Encoder
{
public:
    Encoder(unsigned char pinCHA, unsigned char pinCHB);
    void interrupt();
    void fix();
    int getValue() const;

private:
    const unsigned char pinCHA;
    const unsigned char pinCHB;
    volatile int counter;
    int value;
};

#endif
