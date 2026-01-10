#include "../include/Platform.hpp"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

// Initialisiert Windows-Terminal für ANSI-Sequenzen
void Platform::init()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}

void Platform::cleanup() {}

int Platform::getChar()
{
    return _getch();
}

#else
#include <termios.h>
#include <unistd.h>

static termios oldt;

// Initialisiert Linux-Terminal im Raw-Mode
void Platform::init()
{
    termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Platform::cleanup()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int Platform::getChar()
{
    return getchar();
}
#endif

void Platform::clearScreen()
{
    std::cout << "\033[2J\033[H";
}
