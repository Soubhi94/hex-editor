#ifndef FILEBUFFER_HPP
#define FILEBUFFER_HPP

#include <string>
#include <cstdint>
#include <fstream>
#include <map>

// Verwaltet den Zugriff auf die Datei.
// Bytes werden bei Bedarf von der Festplatte gelesen.
// Geänderte Bytes werden im Overlay-Puffer gespeichert und beim Speichern gezielt in die Datei zurückgeschrieben.
class FileBuffer
{
private:
    std::string path;
    mutable std::ifstream fileStream;
    size_t fileSize = 0;

    std::map<size_t, uint8_t> modifiedBytes;
    bool dirty = false;

public:
    ~FileBuffer();

    bool open(const std::string &filename);
    bool save();

    uint8_t getByte(size_t index) const;
    void setByte(size_t index, uint8_t value);

    size_t size() const;
    bool isDirty() const { return dirty; }
};

#endif
