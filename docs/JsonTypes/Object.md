# Object

Klasa implementująca interfejs [Json](./Json.md).  
Buduje abstrakcję nad obiektami JSON.

```cpp
class Object : public Json
```

Klasa zbudowana jest wokół `std::unordered_map< std::string, JsonVariant >`.  
Zrezygnowałem tutaj z dziedziczenia po `std::unordered_map`, by interfejs publiczny tej klasy nie używał [JsonVariant](./JsonVariant.md).

### Konstruktory

```cpp
Object() = default;  
Object(const std::unordered_map< std::string, std::shared_ptr< Json > >& map);  
Object(const Object& other);  
Object(Object&& other) noexcept;  
Object(std::shared_ptr< Allocator > alloc,  PrimObject& prim);
```

- Domyślny (pusty słownik)
- `Object(map)` – utworzy klasę zainicjowaną wskaźnikami i kluczami z otrzymanego `map`
- `Object(const Object& other)` – utworzy klasę pobierając wartość z `other`
- `Object(Object&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `Object(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; wszystkie elementy wskazywane przez typ prymitywny zostaną użyte do utworzenia `JsonVariant`. Później typ prymitywny i tablica wskaźników zostanie zwolniona

### API

#### Operatory

```cpp
Object& operator=(const Object& other);  
Object& operator=(Object&& other) noexcept;  
Object& operator=(const std::unordered_map< std::string, std::shared_ptr< Json > >& map);
```

Jeśli operator przypisania zostanie użyty wraz ze stałą referencją, to elementy zostaną skopiowane. Dla referencji tymczasowej klasy `std::unordered_map` zostaną zamienione miejscami (referencja tymczasowa zostanie od razu usunięta, więc stara `std::unordered_map` również).

W przypadku użycia operatora przypisania wraz mapą dane zawarte w `Object` zostaną usunięte i pusta mapa zostanie wypełniona zbiorem kluczy i wartości.

---

```cpp
Json& operator[](const std::string& key);
```

Tak jak w przypadku klasycznych obiektów możliwe jest użycie operatora `[]` do wykonania dostępu do elementów `Object`.

Jeśli nie istnieje obiekt dopasowany do klucza `key`, to zostanie utworzony nowy obiekt typ `json::Null` i dodany jako mapowanie dla tego klucza.  
Nie zwracany jest wyjątek, by interfejs był podobny do `std::unordered_map`.

#### Funkcje

```cpp
std::size_t size() const;
```

Pozwoli pobrać ilość elementów znajdujących się w `Object`.

---

```cpp
void emplace(const std::string& key, Json& value);
void emplace(const std::string& key, Json&& value);
void emplace(const std::string& key, const std::shared_ptr< Json >& value);
```

Funkcje pozwalają na dodawanie elementów do obiektu.  
Możliwe oprócz klucza na pierwszym argumencie możliwe jest przekazanie referencji bądź tymczasowej referencji na obiekt `Json` (w tym wariancie bez kopii).

---

```cpp
bool contains(const std::string& key) const;  
std::optional< std::reference_wrapper< Json > > getOpt(const std::string& key);
```

Funkcja `contains` pozwala sprawdzić, czy istnieje mapowanie w obiekcie dla wybranego klucza.  
Funkcja `getOpt` zwróci referencję na element pod kluczem `key` tylko jeśli istnieje mapowanie dla tego klucza.

---

```cpp
void erase(const std::string& key);
```

Funkcja pozwala usunąć wybrany element obiektu.

---

```cpp
void clear();
```

Pozwala usunąć wszystkie elementy obiektu.

---

```cpp
std::shared_ptr< Json >& getOwner(const std::string& key);
```

Pozwala pobrać referencje na wskaźnik będący właścicielem elementu zmapowanego do `key`.  
Używane do konwersji typów elementów już znajdujących się w obiekcie za pomocą funkcji `Json::castTo`.

#### Iterator

```cpp
iterator begin();  
iterator end();
```

Klasa implementuje concept iteratora z użyciem klasy `ObjectIterator`.  
Udostępniony jest standardowy interfejs iteratora, w tym:

- `iterator(Object& arr, std::unordered_map< std::string, JsonVariant >::iterator it)` – konstruktor (potrzebny jest iterator na wewnętrzny obiekt)
- `std::pair< std::string, Json& >& operator*()` – operator pobierania referencji na aktualny element
- `iterator& operator++()` – operator pozwalający przejść do następnego elementu

> **Nie** implementowany jest concept stałego iteratora.