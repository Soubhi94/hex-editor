#include "../include/StateManager.hpp"

// Startposition auf Byte 0
StateManager::StateManager() : cursorPosition(0), windowOffset(0) {}

void StateManager::moveUp()
{
    if (cursorPosition >= bytesPerLine)
        cursorPosition -= bytesPerLine;
}

void StateManager::moveDown(size_t totalSize)
{
    if (cursorPosition + bytesPerLine < totalSize)
        cursorPosition += bytesPerLine;
}

void StateManager::moveLeft()
{
    if (cursorPosition > 0)
        cursorPosition--;
}

void StateManager::moveRight(size_t totalSize)
{
    if (cursorPosition + 1 < totalSize)
        cursorPosition++;
}
