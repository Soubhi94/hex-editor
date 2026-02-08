#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <cstddef>

// Verwaltet Cursorposition und Fenster-Offset, um eine scrollbare Ansicht im Editor zu ermöglichen.
class StateManager
{
private:
    size_t cursorPosition;
    size_t windowOffset;

    const size_t bytesPerLine = 8;
    const size_t linesPerPage = 20;

public:
    StateManager();

// Invarianten:
// - cursorPosition bleibt innerhalb [0, totalSize-1] (geclamped durch moveDown/moveRight).
// - windowOffset ist immer so gewählt, dass cursorPosition im sichtbaren Bereich liegt.
// - windowOffset bewegt sich in Schritten von bytesPerLine (zeilenweise Scrollen).

    void moveUp();
    void moveDown(size_t totalSize);
    void moveLeft();
    void moveRight(size_t totalSize);

    size_t getCursorPos() const { return cursorPosition; }
    size_t getOffset() const { return windowOffset; }
    size_t getBytesPerLine() const { return bytesPerLine; }
};

#endif

