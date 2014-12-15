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


OK, widze ze umknelo to waszej uwadze:

1) wszelkie nowe pliki kodu zrodlowego maja sie znalezc w KATALOGU SRC

2) wszelkie includy maja miec sciezki RELATYWNE OD KATALOGU src/

3) WSZYSTKIE PLIKI NALEZACE TYLKO DO SERWERA -> KATALOG SERWER, a WSZYSTKIE PLIKI NALEZACE TYLKO DO KLIENTA -> KATALOG KLIENT

4) WSZYSTKIE PLIKI PRAWDOPODOBNIE WSPOLDZIELONE PRZEZ SERWER/KLIENT -> KATALOG SHARED

5) NIE TWORZYC NOWYCH KATALOGOW OSOBNO NA KAZDA KLASE

6) po dodaniu nowego pliku .cpp NALEZY UPDATEOWAC PLIK src/CMakeLists.cpp w miejscu set("commonSRCS"... W PORZADKU ALFABETYCZNYM

7) ZABRANIAM tworzenia plikow o nazwie "main.cpp"

8) od teraz PROSZE TESTOWAC swoje dzieci tworzac stosowne testy w katalogu src/test na wzor pliku TemplateTest.h (tylko zrobic rozzserzenie .cpp zamiast .h, dalem .h zeby mi go nie kompilowal cmake)

9) jak korzystacie z jakichs edytorow, co tworza pliki tymczasowe, np. costam.autosave (o Tobie mowa, Pawle), to dodajcie sobie w .gitignore na samym dole dyrektywe, zeby takich smieci nie wrzucac na serwer w commitach. Dla tego przypadku byloby to *.autosave

10) obecnie sie testuje przy pomocy make test. pliki wykonywalnie nie sa juz w build/src, a po prostu w build. Mozna tez odpalac poszczegolne klasy testow, jezeli sie dobrze to napisalo (np testy tylko konkretnej klasy). Generalnie jeden plik testowy powinien przypadac na jedną klase.

11) PODCZAS KOMPILACJI MA NIE BYC ZADNYCH WARNINGOW!


pewnie jeszcze wyjda jakies kwiatki...
