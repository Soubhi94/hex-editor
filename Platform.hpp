#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <string>

namespace Platform
{
    // Initialisierung des Terminals (Raw-Mode / ANSI)
    void init();
    void cleanup();
    void clearScreen();

    // Liest Tastendruck sofort (blockierend)
    int getChar();

    // Spezielle Tastencodes
    const int KEY_UP = 1001;
    const int KEY_DOWN = 1002;
    const int KEY_LEFT = 1003;
    const int KEY_RIGHT = 1004;
    const int KEY_ENTER = 13;
    const int KEY_BACKSPACE = 8;
    const int KEY_ESCAPE = 27;

    // ANSI-Farben
    const std::string ANSI_RESET = "\033[0m";
    const std::string ANSI_RED_BG = "\033[41m\033[97m";
}

#endif
