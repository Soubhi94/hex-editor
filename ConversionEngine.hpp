#ifndef CONVERSIONENGINE_HPP
#define CONVERSIONENGINE_HPP

#include <string>
#include <cstdint>


// Stellt Hilfsfunktionen bereit, um einzelne Bytes in Hex-, Binär- und ASCII-Darstellung umzuwandeln.
// Zusätzlich werden Benutzereingaben validiert und in echte Byte-Werte konvertiert.
class ConversionEngine
{
public:
    static std::string toHex(uint8_t byte);
    static std::string toBin(uint8_t byte);
    static char toChar(uint8_t byte);

    static bool parseHexByte(const std::string &s, uint8_t &out);
    static bool parseBinByte(const std::string &s, uint8_t &out);
};

#endif

