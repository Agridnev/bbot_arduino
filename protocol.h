#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "serialdatagram.h"

class Protocol
{
public:
    struct Data
    {
        long int x;
        long int y;
        short int th;
        short int linear;
        short int angular;
        unsigned char enabled;
        unsigned char voltage;
    };

    struct Motors
    {
        unsigned char enable;
    };

    struct Velocity
    {
        short int linear;
        short int angular;
    };

    typedef void (&CallbackMotors)(const Motors&);
    typedef void (&CallbackVelocity)(const Velocity&);

    Protocol(CallbackMotors cbMotors, CallbackVelocity cbVelocity);
    void send(const Data &data);
    void receive();

private:
    CallbackMotors cbMotors;
    CallbackVelocity cbVelocity;
    sd::Serializer serializer;
    sd::Deserializer deserializer;
};

#endif
