#include <iostream>
#include <string>
#include <functional>
#include "include/Platform.hpp"
#include "include/FileBuffer.hpp"
#include "include/StateManager.hpp"
#include "include/EditorUI.hpp"
#include "include/ConversionEngine.hpp"

// Hilfsfunktion: Liest Input in Zeile 25
std::string readInput(const std::string &prompt, std::function<bool(char)> validator = nullptr, size_t maxLength = 0)
{
    std::cout << "\033[25;0H\033[K"; // Zeile 25 löschen
    std::cout << prompt;

    std::string input;

    while (true)
    {
        int key = Platform::getChar();

        if (key == Platform::KEY_ENTER)
        {
            break;
        }
        else if (key == Platform::KEY_BACKSPACE)
        {
            if (!input.empty())
            {
                input.pop_back();
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (key == Platform::KEY_ESCAPE)
        {
            return "";
        }
        else if (key >= 32 && key <= 126)
        {
            if (maxLength > 0 && input.length() >= maxLength)
                continue;
            if (validator && !validator((char)key))
                continue;

            input += (char)key;
            std::cout << (char)key << std::flush;
        }
    }

    std::cout << "\033[25;0H\033[K";
    return input;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Benutzung: ./hexeditor <datei>\n";
        return 1;
    }

    Platform::init();

    FileBuffer fb;
    if (!fb.open(argv[1]))
    {
        std::cerr << "Fehler: Datei nicht lesbar!\n";
        return 1;
    }

    StateManager state;
    bool running = true;

    Platform::clearScreen();

    while (running)
    {
        EditorUI::draw(fb, state);

        int key = Platform::getChar();

        // NAVIGATION (Pfeile + WASD)
        if (key == 'w' || key == 'W' || key == Platform::KEY_UP)
            state.moveUp();
        else if (key == 's' || key == 'S' || key == Platform::KEY_DOWN)
            state.moveDown(fb.size());
        else if (key == 'a' || key == 'A' || key == Platform::KEY_LEFT)
            state.moveLeft();
        else if (key == 'd' || key == 'D' || key == Platform::KEY_RIGHT)
            state.moveRight(fb.size());

        // BEENDEN (Q)
        else if (key == 'q' || key == 'Q')
        {
            if (fb.isDirty())
            {
                std::cout << "\033[25;0H\033[K";
                std::cout << "\033[41m\033[97m AENDERUNGEN VORHANDEN! Speichern? [Enter]=Ja, [Andere]=Nein \033[0m";

                int choice = Platform::getChar();
                if (choice == Platform::KEY_ENTER)
                {
                    if (fb.save())
                    {
                        std::cout << "\033[25;0H\033[K Gespeichert.";
                    }
                    else
                    {
                        std::cout << "\033[25;0H\033[K Speicherfehler! Taste druecken.";
                        Platform::getChar();
                    }
                }
            }
            running = false;
        }

        //  HEX EDIT (H)
        else if (key == 'h' || key == 'H')
        {
            auto hexValidator = [](char c)
            { return isxdigit(c); };
            std::string s = readInput("HEX Eingabe (z.B. A9): ", hexValidator, 2);
            if (!s.empty())
            {
                uint8_t val;
                if (ConversionEngine::parseHexByte(s, val))
                    fb.setByte(state.getCursorPos(), val);
            }
        }

        // TEXT EDIT (T) 
        else if (key == 't' || key == 'T')
        {
            std::cout << "\033[25;0H\033[KZEICHEN Eingabe: ";
            int c = Platform::getChar();
            if (c >= 32 && c <= 126)
            {
                fb.setByte(state.getCursorPos(), (uint8_t)c);
            }
            std::cout << "\033[25;0H\033[K";
        }

        // BINÄR EDIT (B) 
        else if (key == 'b' || key == 'B')
        {
            auto binValidator = [](char c)
            { return (c == '0' || c == '1'); };
            std::string binStr = readInput("BINAER Eingabe (8 Bits): ", binValidator, 8);

            if (!binStr.empty())
            {
                uint8_t val;
                if (ConversionEngine::parseBinByte(binStr, val))
                    fb.setByte(state.getCursorPos(), val);
            }
        }
    }

    Platform::clearScreen();
    Platform::cleanup();
    return 0;
}
