#include "../include/EditorUI.hpp"
#include "../include/ConversionEngine.hpp"
#include "../include/Platform.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

// Hinweis: Offset-Anzeige ist aktuell auf 16-bit (2 Byte) formatiert.
// Für Dateien > 65535 Bytes wiederholt sich die Anzeige; Datenzugriff bleibt korrekt.

void EditorUI::draw(const FileBuffer &fb, const StateManager &state)
{
    std::stringstream ss;
    ss << "\033[H"; // Cursor nach Home

    ss << "--- HYBRID HEX EDITOR [" << (fb.isDirty() ? "MODIFIED" : "SAVED") << "] ---\n\n";

    // 3 Spalten Header
    ss << "Offset   | Hex (8b)                 | Binary (8b)                              | Text    \n";
    ss << "---------|--------------------------|------------------------------------------|---------\n";

    size_t start = state.getOffset();
    const size_t ROWS = 20;
    const size_t BPL = state.getBytesPerLine();

    for (size_t row = 0; row < ROWS; ++row)
    {
        size_t rowAddr = start + (row * BPL);

        // Adresse
        if (rowAddr < fb.size())
            ss << ConversionEngine::toHex((uint8_t)(rowAddr >> 8))
               << ConversionEngine::toHex((uint8_t)(rowAddr & 0xFF)) << "  | ";
        else
            ss << "      | ";

        // 1. HEX
        for (size_t i = 0; i < BPL; ++i)
        {
            size_t addr = rowAddr + i;
            if (addr < fb.size())
            {
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RED_BG;
                ss << ConversionEngine::toHex(fb.getByte(addr));
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RESET;
                ss << " ";
            }
            else
                ss << "   ";
        }
        ss << "| ";

        // 2. BINARY
        for (size_t i = 0; i < BPL; ++i)
        {
            size_t addr = rowAddr + i;
            if (addr < fb.size())
            {
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RED_BG;
                ss << ConversionEngine::toBin(fb.getByte(addr));
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RESET;
                ss << " ";
            }
            else
                ss << "         ";
        }
        ss << "| ";

        // 3. TEXT
        for (size_t i = 0; i < BPL; ++i)
        {
            size_t addr = rowAddr + i;
            if (addr < fb.size())
            {
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RED_BG;
                ss << ConversionEngine::toChar(fb.getByte(addr));
                if (addr == state.getCursorPos())
                    ss << Platform::ANSI_RESET;
            }
            else
                ss << " ";
        }
        ss << "\n";
    }

    ss << "\n[Arrows/WASD] Move | [H] Hex | [B] Bin | [T] Text | [Q] Quit\n";
    ss << "Pos: " << state.getCursorPos() << " / " << fb.size() << "\n";

    std::cout << ss.str() << std::flush;
}

