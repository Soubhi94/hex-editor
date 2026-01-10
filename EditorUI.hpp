#ifndef EDITORUI_HPP
#define EDITORUI_HPP

#include "FileBuffer.hpp"
#include "StateManager.hpp"

// Erzeugt die tabellarische Darstellung der Datei im Terminal.
// Offset, Hex-, Binär- und ASCII-Spalten werden angezeigt.
// Der Cursor wird farblich hervorgehoben.
class EditorUI
{
public:
    static void draw(const FileBuffer &fb, const StateManager &state);
};

#endif
