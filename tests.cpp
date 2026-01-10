#include <iostream>
#include <cassert>
#include "include/ConversionEngine.hpp"
#include "include/StateManager.hpp"

void testConversion()
{
    std::cout << "Test ConversionEngine... ";

    assert(ConversionEngine::toHex(255) == "FF");
    assert(ConversionEngine::toBin(1) == "00000001");

    uint8_t val;
    assert(ConversionEngine::parseHexByte("FF", val) && val == 255);
    assert(ConversionEngine::parseBinByte("00000011", val) && val == 3);

    std::cout << "OK\n";
}

void testStateManager()
{
    std::cout << "Test StateManager... ";

    StateManager sm;
    assert(sm.getCursorPos() == 0);
    sm.moveDown(100);
    assert(sm.getCursorPos() == sm.getBytesPerLine());

    std::cout << "OK\n";
}

int main()
{
    testConversion();
    testStateManager();
    std::cout << "Alle Tests OK.\n";
    return 0;
}
