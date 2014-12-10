RebeliaProgramowalnychZaskroncow
================================

Programmable 'Achtung die Kurve' multiplayer internet game. RPZ in short


Aby skompilować projekt należy:
utworzyc katalog build
wejsc w katalog
wpisac cmake ..
nastepnie make
wejsc w utworzony katalog src
tam bedzie exec.

Aby utworzyc dokumentacje nalezy wykorzystac skrypt generatedocs.sh

Aby ustandaryzowac skladnie plikow nalezy uzyc skryptu astyle.sh

Polecam przed commitem uzywac mojego aliasu "suchastyle" ktory odpali automatycznie ten skrypt na wszystkich plikach c++ zmienionych w tym commicie.
Jezeli nie dziala wam "suchastyle", to przekopiujcie sobie zawartość z config/.bashrc do swojego lokalnego ~/.bashrc.

Polecam, żeby nie zapominac o odpalaniu astyle.sh, zrobic alias typu "suchastyle | git commit" - przyklad macie w config/.bashrc

Jezeli astyle wam nie dziala, oznacza ze musicie sobie je sciagnac (z repo).
