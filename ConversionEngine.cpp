#include "../include/ConversionEngine.hpp"
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cctype>

// Wandelt ein Byte in einen zweistelligen Hex-String um
std::string ConversionEngine::toHex(uint8_t byte)
{
    std::stringstream ss;
    ss << std::hex << std::setw(2)
       << std::setfill('0') << std::uppercase
       << static_cast<int>(byte);
    return ss.str();
}

// Wandelt ein Byte in einen 8-Bit Binär-String um
std::string ConversionEngine::toBin(uint8_t byte)
{
    return std::bitset<8>(byte).to_string();
}

// Gibt ein druckbares ASCII-Zeichen zurück, nicht druckbare Bytes werden als Punkt dargestellt
char ConversionEngine::toChar(uint8_t byte)
{
    return (std::isprint((unsigned char)byte)) ? (char)byte : '.';
}

// Validiert und parst zweistellige Hex-Eingabe
bool ConversionEngine::parseHexByte(const std::string &s, uint8_t &out)
{
    if (s.size() != 2) return false;
    try {
        int val = std::stoi(s, nullptr, 16);
        out = (uint8_t)val;
        return true;
    } catch (...) {
        return false;
    }
}

// Validiert und parst 8-Bit Binäreingabe
bool ConversionEngine::parseBinByte(const std::string &s, uint8_t &out)
{
    if (s.size() != 8) return false;
    try {
        std::bitset<8> b(s);
        out = (uint8_t)b.to_ulong();
        return true;
    } catch (...) {
        return false;
    }
}
