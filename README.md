# Hybrid Hex Editor

Plattformunabhängiger Hex-Editor für die Konsole zur Analyse und
Bearbeitung sehr großer Binärdateien ohne vollständiges Laden in den
Arbeitsspeicher.

## Funktionen

-   Gleichzeitige Anzeige von Hex, Binär und ASCII
-   Direkter Dateizugriff ohne vollständiges Laden in den RAM
-   Änderungen werden als Overlay im Speicher gehalten und erst beim
    Speichern gepatcht
-   Läuft auf Windows, Linux und macOS ohne externe Bibliotheken
-   Validierte Eingabe für Hex- und Binärwerte

## Kompilieren

Voraussetzung: C++17 Compiler (GCC, Clang oder MSVC)

``` bash
g++ -std=c++17 main.cpp src/*.cpp -I include -o hexeditor
```

Wichtig: `tests.cpp` darf hier nicht enthalten sein.

Unit-Tests separat:

``` bash
g++ -std=c++17 tests.cpp src/*.cpp -I include -o run_tests
```

## Start

``` bash
./hexeditor datei.bin      # Linux / macOS
hexeditor.exe datei.bin    # Windows
```

## Steuerung

Navigation: - Pfeiltasten oder W A S D

Editieren: - H -- Hex-Wert eingeben (z.B. FF) - B -- Binärwert eingeben
(z.B. 01010101) - T -- ASCII-Zeichen eingeben

System: - Q -- Beenden (fragt bei ungespeicherten Änderungen)

## Einschränkungen

-   Mindestgröße Terminal: 100 Zeichen Breite, 25 Zeilen Höhe
-   In alter Windows cmd.exe leichtes Flackern möglich
-   Nicht druckbare ASCII-Zeichen werden als Punkt dargestellt
