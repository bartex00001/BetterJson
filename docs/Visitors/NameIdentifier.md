# NameIdentifier

Klasa implementująca interfejs [Visitor](./Visitor.md).  
Działa jak funktor pozwalający na pobranie nazwy podklasy [Json](../JsonTypes/Json.md) jako tekstu.

```cpp
class NameIdentifier : public Visitor
```

> Funkcjonalność pozwalająca na pobranie nazwy typu znajduje się w bibliotece systemowej `cxxabi.h`, ale jest dostępna tylko na systemach linux

### Konstruktor

```cpp
NameIdentifier() = default;
```

Dostępny jest tylko konstruktor domyślny.

### Operator Funkcyjny

```cpp
std::string operator()(Json& json);  
std::string operator()(Json&& json);
```

Dostępne są dwa warianty operatora funkcyjnego – jeden dla referencji, a drugi dla wartości tymczasowych. Oba działają tak samo – zwracają nazwę przekazanego typu.

## Przykład

```cpp
// Dla json: Json& będącego referencją do typu String
std::cout << NameIdentifier()(json); // String 
```