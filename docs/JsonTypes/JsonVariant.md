# JsonVariant

Klasa pozwalająca na leniwą transformację typów z [PrimVariant](../PrimTypes/PrimVariant.md).

```cpp
class JsonVariant
```

Obiekt wewnątrz zawiera *type-safe* unię (`std::variant`), która może być w dwóch stanach:

1. `std::shared_ptr< Json >` – właściciel abstrakcyjnego typy [Json](./Json.md)
2. `std::reference_wrapper< PrimVariant >` – właściciel [PrimVariant](../PrimTypes/PrimVariant.md); W tym stanie klasa przechowuje jest również właścicielem alokatora użytego do utworzenia `PrimVariant`.

> Dla `PrimVariant` użyłem typu `std::reference_wrapper`, ponieważ wartość ma być nie-pusta i nie narzucać zarządzania pamięci (bo jest ono robione ręcznie).


### Konstruktory

```cpp
JsonVariant() = default;  
JsonVariant(PrimVariant& primVariant, std::shared_ptr< Allocator > alloc);  
JsonVariant(std::shared_ptr< Json > jsonType);
```

Dostępne są następujące konstruktory:

- Domyślny – istnieje tylko dlatego, że kontenery biblioteki standardowej C++ wymuszają jego istnienie dla swoich typów wartości. Unia zostanie zainicjalizowana z pustym `std::shared_ptr< Json >`
- `JsonVariant(primVariant, alloc)` – zainicjuje unię na referencję na `PrimVariant` oraz utworzy wskaźnik z własnością dla `alloc`
- `JsonVarinat(jsonType)` – zainicjuje unię dzielonym wskaźnikiem na typ `Json`

### API

```cpp
std::shared_ptr< Json >& getInsideJsonRef();  
```

Pozwala pobrać referencję na oryginalny wskaźnik przechowywane przez klasę.  
Jeśli unia jest w stanie przechowującym `PrimVariant`, to wykona konwersję do odpowiedniej podklasy `Json`, zapisze wynik jako `shared_ptr` w unii oraz usunie własność alokatora.

> Nie koniecznie oznacza to usunięcie alokatora – `shared_ptr` działa na zasadzie zliczania referencji

---

```cpp
std::shared_ptr< Json > getJson();
```

Pozwala pobrać kopię *wskaźnika z własnością* znajdującego się wewnątrz klasy.  
Wewnętrznie używa `getInsideJsonRef`.

> Dane nie są kopiowane; tworzony jest drugi wskaźnik, który też jest właścicielem tych danych
