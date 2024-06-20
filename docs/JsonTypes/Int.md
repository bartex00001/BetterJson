# Int

Klasa implementująca interfejs [Json](./Json.md).
Buduje abstrakcję nad typem int w JSON.

```cpp
class Int : public Json
```

### Konstruktory

```cpp
Int() = default;  
Int(long long val);  
Int(const Int& other);  
Int(Int&& other) noexcept;  
Int(std::shared_ptr< Allocator > alloc, PrimInt& prim);
```

Dostępne są następujące konstruktory:

- Domyślny (wartość zerowa)
- `Int(int val)` – utworzy klasę o wartości `val`
- `Int(const Int& other)` – utworzy klasę pobierając wartość z `other`
- `Int(Int&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `Int(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; usunie przekazany typ prymitywny

### API

#### Operatory

```cpp
long long& operator=(long long val);  
Int& operator=(const Int& other);  
Int& operator=(Int&& other) noexcept;
```

Możliwe jest użycie operatora przypisania ze stałą lub tymczasową referencją na `Int` oraz prymitywnym typem `long long`.  
W każdym przypadku konstruktor zadziała tak jak można tego oczekiwać – ustawi wartość obiektu na przekazaną.

---

```cpp
operator long long&();
```

Pozwoli na automatyczną konwersję do prymitywnego typu `bool`.

Przykład:

```cpp
void foo(int);

// w main
json::Int i(123);
foo(i); // automatyczna konwersja do int (nie musi to być dokładnie long long!)
```

#### Funkcje

```cpp
long long& value();
```

Pozwala pobrać referencję na wewnętrzną wartość.