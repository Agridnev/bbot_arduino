// Serial Datagram format:
// 1 byte  - Header: magic (0xA5)
// 1 byte  - Header: length of Data (n = 0..252)
// 1 byte  - Header: CRC-8/CDMA2000 of Data
// n bytes - Data (optional)
// Total: 3..255 bytes

#ifndef SERIALDATAGRAM_H
#define SERIALDATAGRAM_H

namespace sd
{

    const unsigned char magic = 0xA5;
    const unsigned int maxSLength = 255;
    const unsigned int maxDLength = 252;

    class Serializer
    {
    public:
        Serializer();
        void serialize(const unsigned char *dData, unsigned char dLength);
        const unsigned char *getSData();
        unsigned char getSLength();
    private:
        unsigned char sData[maxSLength];
        unsigned char sLength;
    };

    class Deserializer
    {
    public:
        Deserializer();
        void append(const unsigned char *sData, unsigned char sLength);
        void deserialize();
        const unsigned char *getDData();
        unsigned char getDLength();
    private:
        unsigned char buffer[2 * maxSLength];
        unsigned char *dData;
        unsigned char dLength;
        unsigned char *pendingData;
        unsigned int pendingLength;
    };

}

#endif

