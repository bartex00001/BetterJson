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
Czytanie najlepiej zacząć od [Spisu Klas](./docs/SpisKlas.md).

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

Wykonywane z użyciem klasy [Parser](./Parser/Parser.md). Możliwe jest parsowanie plików, strumieni i buforów:

```cpp
auto jsonCin{json::Parser<>::parse(std::cin)}; // parsuj strumień wejściowy

auto jsonBuffer{json::Parser<>::parse(buffor)}; // parsuj bufor

auto file{json::FileStream("test.json")};
auto jsonFile{json::Parser<>::parse(file)}; // parsuj plik "test.json"
```

#### Klasa [Json](./JsonTypes/Json.md)

Jest to interfejs implementowany przez klasy reprezentujące typy wartości JSON.  
Jako że jest to klasa abstrakcyjna zawsze będzie w formie:

- `Json&` – referencji bez własności nad obiektem
- `std::shared_ptr< Json >` – wskaźnika z własnością nad obiektem

#### Typy Wartości

Implementują interfejs podobny do prymitywnych / STL'owych odpowiedników:

```cpp
json::Int i = 23;
i += 121;

json::String str("some text");
str.append(" more text");

json::Array arr{};
arr.push_back(i);
foo(arr[0]);

json::Object obj;
obj.emplace(str, i);
std::cout << obj[str];
```

#### Pobieranie Podklasy z Json

Jeśli dysponujemy referencją lub wskaźnikiem na `Json`, to by skorzystać z interfejsu udostępnionego przez podklasę należy wykonać konwersję. Pozwala na to funkcja `as< T >` zaimplementowana dla typu `Json`:

```cpp
obj[key].as< json::Int >() = 42;
```

Jeśli referencja na `Json` tak naprawdę nie jest typu `T` to rzucony zostanie wyjątek `json::BadCast`.

#### Konwersja Typu Wartości

Jest to wyjątkowo destruktywna operacja stąd dostępna jest tylko dla właścicieli obiektów (`std::shared_ptr`). W momencie wykonania należy uznać wszystkie nie-posiadające referencje za niepoprawne.

Konwersji można dokonać używając statycznej funkcji `json::Json::castTo< T >`:

```cpp
json::Json::castTo< json::Bool >(arr[0]);
```

Jeśli spróbujemy castować na ten typ, którym obiekt już jest, to funkcja nie będzie mieć efektu.

#### Wypisywanie

Klasa `Json` posiada nadpisany operator `<<`, stąd do wypisania struktury można skorzystać ze standardowego interfejsu strumieni C++:
```cpp
std::cout << json;
```

Format wypisywania można dostosować używając funktora [Printer](./docs/Visitors/Printer.md).

## Next Steps

Co można zrobić dalej:

- Poprawić strategię [MemoryPool](./Allocators/MemoryPool.md) – teraz jest bardzo prosta
- Pozwolić na wykonywanie większej ilości operacji na stałych referencjach do podklas `Json` – obecnie prawie nic nie można z nimi zrobić
- Umożliwić wykonywanie operacji read-only bez konwertowania typów prymitywnych do abstrakcyjnych