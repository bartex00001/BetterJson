# String

Klasa implementująca interfejs [Json](./Json.md).
Buduje abstrakcję nad wartościami tekstowymi JSON.

```cpp
class String : public Json, public std::string
```

### Konstruktory

```cpp
String() = default;  
String(const std::string& str);  
String(const String& other);  
String(String&& other) noexcept;  
String(std::shared_ptr< Allocator > alloc, PrimString& prim);
```

Dostępne są następujące konstruktory:

- Domyślny (pusty napis)
- `String(const std::string& str)` – utworzy klasę zainicjowaną przekazanym napisem
- `String(const String& other)` – utworzy klasę pobierając wartość z `other`
- `String(String&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `String(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; usunie przekazany typ prymitywny (oraz napis w nim zawarty jeśli `prim` jest jego właścicielem)

### API

```cpp
std::string& value();
```

Pozwala pobrać referencję na wewnętrzną wartość.  
Funkcja dostępna jest, by zachować spójność z pozostałymi podklasami Json.

---

Jako że `json::String` jest podklasą `std::string`, to dziedziczy cały jej interfejs i może być wszędzie, gdzie wykorzystywane są wskaźniki i referencje na typ `std::string` dzięki polimorfizmowi.