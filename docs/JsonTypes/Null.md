# Null

Klasa implementująca interfejs [Json](./Json.md).
Buduje abstrakcję nad typem `null` w JSON.

```cpp
class Null : public Json
```

### Konstruktory

```cpp
Null() = default;  
Null(const Null&);  
Null(Null&&) noexcept;  
Null(std::shared_ptr< Allocator > alloc, PrimNull& pNull);
```

Dostępne są następujące konstruktory:

- Domyślny
- `Null(const Null&)` – konstruktor z referencji
- `Null(Null&&)` – konstruktor z referencji tymczasowej
- `Null(alloc, pNull)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; usunie przekazany typ prymitywny