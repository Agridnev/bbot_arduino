#include <Arduino.h>

#include "protocol.h"

byte buffer[64];

Protocol::Protocol(CallbackMotors cbMotors, CallbackVelocity cbVelocity) : cbMotors(cbMotors), cbVelocity(cbVelocity)
{
}

void Protocol::send(const Data &data)
{
    serializer.serialize((const unsigned char *) &data, sizeof(data));
    Serial.write(serializer.getSData(), serializer.getSLength());
}

void Protocol::receive()
{
    while (int available = Serial.available())
    {
        int length = min(sizeof(buffer), available);
        Serial.readBytes(buffer, length);
        deserializer.append(buffer, length);
        deserializer.deserialize();
        while(deserializer.getDLength())
        {
            if (deserializer.getDLength() == sizeof(Motors))
            {
                cbMotors(*(Motors *) deserializer.getDData());
            }
            else if (deserializer.getDLength() == sizeof(Velocity))
            {
                cbVelocity(*(Velocity *) deserializer.getDData());
            }
            deserializer.deserialize();
        }
    }
}
