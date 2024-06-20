# Bool

Klasa implementująca interfejs [Json](./Json.md).
Buduje abstrakcję nad typem boolean w JSON.

```cpp
class Bool : public Json
```

### Konstruktory

```cpp
Bool() = default;  
Bool(bool val);  
Bool(const Bool& other);  
Bool(Bool&& other) noexcept;  
Bool(std::shared_ptr< Allocator > alloc, PrimBool& prim);
```

Dostępne są następujące konstruktory:

- Domyślny (wartość fałszywa)
- `Bool(bool val)` – utworzy klasę o wartości `val`
- `Bool(const Bool& other)` – utworzy klasę pobierając wartość z `other`
- `Bool(Bool&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `Bool(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; usunie przekazany typ prymitywny

### API

#### Operatory

```cpp
bool& operator=(bool val);  
Bool& operator=(const Bool& other);  
Bool& operator=(Bool&& other) noexcept;
```

Możliwe jest użycie operatora przypisania ze stałą lub tymczasową referencją na `Bool` oraz prymitywnym typem `bool`.  
W każdym przypadku konstruktor zadziała tak jak można tego oczekiwać – ustawi wartość obiektu na przekazaną.

---

```cpp
operator bool&();
```

Pozwoli na automatyczną konwersję do prymitywnego typu `bool`.

Przykład:

```cpp
void foo(bool);

// w main
json::Bool b(true);
foo(b); // automatyczna konwersja do bool
```

#### Funkcje

```cpp
bool& value();
```

Pozwala pobrać referencję na wewnętrzną wartość.