# Float

Klasa implementująca interfejs [Json](./Json.md).
Buduje abstrakcję nad typem int w JSON.

```cpp
class Float : public Json
```

### Konstruktory

```cpp
Float() = default;  
Float(double val);  
Float(const Float& other);  
Float(Float&& other) noexcept;  
Float(std::shared_ptr< Allocator > alloc, PrimFloat& prim);
```

Dostępne są następujące konstruktory:

- Domyślny (wartość zerowa)
- `Float(double val)` – utworzy klasę o wartości `val`
- `Float(const Float& other)` – utworzy klasę pobierając wartość z `other`
- `Float(Float&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `Float(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; usunie przekazany typ prymitywny

### API

#### Operatory

```cpp
double& operator=(double val);  
Float& operator=(const Float& other);  
Float& operator=(Float&& other) noexcept;
```

Możliwe jest użycie operatora przypisania ze stałą lub tymczasową referencją na `Float` oraz prymitywnym typem `double`.  
W każdym przypadku konstruktor zadziała tak jak można tego oczekiwać – ustawi wartość obiektu na przekazaną.

---

```cpp
operator double&();
```

Pozwoli na automatyczną konwersję do prymitywnego typu `double`.

Przykład:

```cpp
void foo(float);

// w main
json::Float i(5.25);
foo(i); // automatyczna konwersja do float (nie musi to być dokładnie double!)
```

#### Funkcje

```cpp
double& value();
```

Pozwala pobrać referencję na wewnętrzną wartość.