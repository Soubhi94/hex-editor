#include "../include/FileBuffer.hpp"

// Datei-Stream schließen
FileBuffer::~FileBuffer()
{
    if (fileStream.is_open())
        fileStream.close();
}

// Öffnet Datei und ermittelt Größe
bool FileBuffer::open(const std::string &filename)
{
    path = filename;
    modifiedBytes.clear();
    dirty = false;

    fileStream.open(path, std::ios::binary | std::ios::ate);
    if (!fileStream.is_open()) return false;

    fileSize = (size_t)fileStream.tellg();
    fileStream.clear();
    return true;
}

// Liest Byte entweder aus Overlay oder direkt von Festplatte
uint8_t FileBuffer::getByte(size_t index) const
{
    if (modifiedBytes.count(index))
        return modifiedBytes.at(index);

    fileStream.seekg(index, std::ios::beg);
    char c;
    fileStream.get(c);
    return (uint8_t)c;
}

// Setzt neues Byte in Overlay-Puffer
void FileBuffer::setByte(size_t index, uint8_t value)
{
    modifiedBytes[index] = value;
    dirty = true;
}

// Schreibt alle geänderten Bytes zurück in Datei
bool FileBuffer::save()
{
    std::fstream fs(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs.is_open()) return false;

    for (auto &p : modifiedBytes) {
        fs.seekp(p.first);
        fs.put((char)p.second);
    }

    modifiedBytes.clear();
    dirty = false;
    return true;
}

size_t FileBuffer::size() const { return fileSize; }
