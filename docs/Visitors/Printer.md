# Printer

Klasa implementująca interfejs [Visitor](./Visitor.md).  
Działa jak funktor pozwalający na konwersje każdej podklasy [Json](../JsonTypes/Json.md).

```cpp
class Printer : public Visitor
```

### Konstruktory

```cpp
Printer() = default;  
Printer(unsigned indent);  
```

Klasa posiada dwa konstruktory pozwalające na wybranie ustawień konwersji:

- Domyślny – do indentacji użyte zostaną znaki tabulacji
- `Printer(unsigned ident)` – jednym poziomem indentacji będzie `ident`-wiele spacji

### Operator Funkcyjny

```cpp
std::string operator()(Json& json);
```

Po utworzeniu klasy można skorzystać z niego (wielokrotnie) tak jak z funkcji, przekazując w nawiasach obiekt JSON do konwersji.
## Przykłady

```cpp
// Konwersja json do typu string z tabulatorami
auto res{ json::Printer()(json) };

// Utworzenie Printer z indentacją ustawioną na 4 spacje
auto myPrinter{ Printer(4) };
// Użycie Printer tak jak funkcji
std::cout << myPrinter(jsonObject);
```
