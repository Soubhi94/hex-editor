================================================================================
PROJEKT: HYBRID HEX EDITOR
================================================================================

Ein professioneller, plattformunabhängiger Hex-Editor für die Konsole.
Entwickelt für die Analyse und Bearbeitung von Binärdateien jeder Größe
(Gigabytes+), ohne den Arbeitsspeicher zu belasten.

--------------------------------------------------------------------------------
VORTEILE & FUNKTIONEN
--------------------------------------------------------------------------------
1. Hybrid-Ansicht:     Zeigt Hex, Binär und Text gleichzeitig an.
2. Direct Disk Access: Lädt Dateien nicht in den RAM. Ideal für riesige
                       Dateien (Logs, ISOs, Dumps).
3. Smart Overlay:      Speichert nur Änderungen im RAM. Das Original wird
                       erst beim Speichern ("Patching") geändert.
4. Cross-Platform:     Läuft auf Windows, Linux und macOS ohne Installation
                       von externen Bibliotheken (kein ncurses nötig).
5. Präzise Eingabe:   Strikte Validierung für Hex (0-F) und Binär (0-1).

--------------------------------------------------------------------------------
INSTALLATION & KOMPILIEREN
--------------------------------------------------------------------------------
Voraussetzung: Ein C++ Compiler (GCC, Clang, MSVC) mit C++17 Support.

Schritt 1: Programm kompilieren
Führen Sie diesen Befehl im Terminal aus:

g++ -std=c++17 main.cpp src/*.cpp -I include -o hexeditor

(WICHTIG: 'tests.cpp' darf hier NICHT enthalten sein.)

Optional: Unit-Tests kompilieren 
Um die Tests separat zu bauen:
g++ -std=c++17 tests.cpp src/*.cpp -I include -o run_tests

--------------------------------------------------------------------------------
BENUTZUNG
--------------------------------------------------------------------------------
Starten Sie das Programm mit dem Dateinamen als Argument:

./hexeditor dateiname.bin   (Linux/macOS)
hexeditor.exe dateiname.bin (Windows)

--------------------------------------------------------------------------------
STEUERUNG
--------------------------------------------------------------------------------
Das Programm reagiert sofort auf Tastendruck (kein Enter für Navigation nötig).

[ NAVIGATION ]
  Pfeiltasten / WASD : Cursor bewegen

[ EDITIEREN ]
  H : Hex-Modus    -> Wert eingeben (z.B. FF) -> Enter
  B : Binaer-Modus -> Bits eingeben (z.B. 01010101) -> Enter
  T : Text-Modus   -> Einzelnes Zeichen tippen

[ SYSTEM ]
  Q : Beenden (Fragt bei ungespeicherten Änderungen nach Speichern)

--------------------------------------------------------------------------------
BEKANNTE EINSCHRAENKUNGEN (LIMITATIONS)
--------------------------------------------------------------------------------
1. Terminalgröße:
   Das Interface benötigt mind. 100 Zeichen Breite und 25 Zeilen Höhe.
   Bei kleineren Fenstern kann das Layout verrutschen.

2. Flackern (Windows):
   In der alten 'cmd.exe' kann es zu leichtem Flackern kommen.
   Empfehlung: Nutzen Sie 'Windows Terminal' oder 'PowerShell'.

3. Sonderzeichen:
   Nicht-druckbare Zeichen (0-31) werden im Text-Modus als '.' angezeigt.
