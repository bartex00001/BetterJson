# Json

Klasa wirtualna (interfejs) dla klas budujących abstrakcję nad typami wartości JSON.

```cpp
class Json  
{  
    Json(const Json& other) = delete;  
    Json(Json&& other) = delete;  
    Json& operator=(const Json& other) = delete;  
    Json& operator=(Json&& other) = delete;  
  
protected:  
    Json() = default;  
  
public:  
    template< typename T >  
       requires std::is_base_of_v< Json, T >  
    auto as() -> T&;  
  
    template< typename T >  
       requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
    static void castTo(std::shared_ptr< Json >& json);  
  
    template< typename T >  
       requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
    auto operator=(T& other) -> T&;  
  
    template< typename T >  
       requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
    auto operator=(T&& other) -> T&;  
  
    virtual void accept(class Visitor& visitor) = 0;  

	virtual ~Json() = default; 
};
```

Interfejs wymaga implementacji jedynie funkcji `accept(Visitor&)`.  
Pozostałe funkcje zostały już zaimplementowane.

Dla tej klasy usunięte zostały operatory przypisania i konstruktory – konieczna jest konwersja do podklasy do wykonania tych operacji.

Chroniony konstruktor domyślny jest potrzebny podklasom.

### Implementacje

- [Object](./Object.md)
- [Array](./Array.md) 
- [String](./String.md)
- [Int](./Int.md)
- [Float](./Float.md)
- [Bool](./Bool)
- [Null](./Null.md)

### API

```cpp
template< typename T >  
   requires std::is_base_of_v< Json, T >  
auto as() -> T&;  
```

Spróbuje wykonać cast *siebie* do typu `T` (który musi być podklasą `Json`).  
W przypadku niepowodzenia zostanie rzucony wyjątek [json::BadCast](../Exceptions/BadCast.md).

---

```cpp
template< typename T >  
    requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
static void castTo(std::shared_ptr< Json >& json);
```

Statyczna funkcja pozwalająca na zmianę przechowywanego typu `Json`.  
Wbrew pozorom jest to bardzo destruktywna operacja, więc możliwa jest tylko dla referencji na właściciela podklasy `Json`.

Skutkiem działania będzie zmiana typu **tylko** w przekazanym *shared pointer*.

Przykład działania:

```cpp
std::shared_ptr< Json > json{...};

Json& ref{*json}; // referencja
json::Object copy{json.as< json::object >()}; // kopia
std::shared_ptr< Json > owner{json};

// Zmiana typu na tablice json
json::Json::castTo< json::Array >(json);

ref; // niepoprawne! obiekt został usunięty
copy; // kopia działa normalnie
owner; // osobny właściciel pozostaje bez zmian (jeśli istnieje, to referencje pozostaną poprawne, ale nie należy na tym polegać)
```

Jeśli obiekt już jest typem `T`, to funkcja nie ma efektu.

---

```cpp
template< typename T >  
    requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
auto operator=(T& other) -> T&;

template< typename T >  
    requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)  
auto operator=(T&& other) -> T&;
```

Funkcje pozwalają na uproszczenie formy zapisu przypisywania do Json:
```cpp
// Zamiast np.:
json.as< json::Array >() = other.as< json::Array >();

// Możliwy jest zapis
json = other.as< json::Array >();
```

Jeśli konwersja nie powiedzie się, to zostanie rzucony wyjątek [json::BadCast](../Exceptions/BadCast.md).

Wariant operatora z wartością tymczasową pozwoli uniknąć kopii.

--- 

```cpp
inline std::ostream& operator<<(std::ostream& os, Json& json);
```

Zdefiniowany jest również operator `ostream` dla typu `Json&` pozwalający na trywialne korzystanie ze strumieni.  
Wewnętrznie operator używa klasy [Printer](../Visitors/Printer.md).