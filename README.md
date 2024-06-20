> Bartłomiej Stefański

Biblioteka typu *Header-Only* do pracy z plikami JSON zawierająca parser oraz klasy budujące abstrakcje nad typami JSON.

## Instalacja

Możliwe są dwa sposoby instalacji:
#### Systemowa

Należy pobrać repozytorium projektu, a następnie zawartość folderu `include` przenieść do systemowego katalogu na pliki nagłówkowe (dla systemów linux `/usr/include`).
#### Lokalna

Wystarczy pobrać repozytorium projektu do dowolnego foldera.  
Należy wtedy pamiętać o dodaniu ścieżki repozytorium do miejsc, w których kompilator będzie szukać plików nagłówkowych np. poprzez dodanie parametru: `-I/{ścieżka-do-repozytorium}/include/`.

## Wymagania 

- Kompilator C++ wspierający standard `C++23`; testowane dla `g++ 11.4.0`

## Dokumentacja

Znajduje się w folderze `docs`.  
Czytanie najlepiej zacząć od [Spisu Klas](./docs/SpisKlas.md) lub [PrzegląduProjektu](PrzegladProjektu.md).

#### Przykłady

W folderze `examples` znajdują się trzy proste przykłady:

- `bjq` – formatter/linter plików JSON'
- `reader` – programu czytający plik JSON
- `writer` – program tworzący i wypisujący strukturę JSON

W folderze znajduje się również plik `Makefile`, który skompiluje wszystkie trzy programy oraz przykładowe wejścia dla tych programów.

## Quick Start

#### Include

Wystarczy dołączyć jeden plik:

```cpp
#include <BetterJson/json.hpp>
```

*Nie należy* dołączać innych plików.

#### Parsowanie

#### Wypisywanie

Klasa `Json` posiada nadpisany operator `<<`, stąd do wypisania struktury można skorzystać ze standardowego interfejsu strumieni C++:
```cpp
std::cout << json;
```

Format wypisywania można dostosować używając funktora [Printer](./docs/Visitors/Printer.md).
