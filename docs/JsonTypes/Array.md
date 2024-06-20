# Array

Klasa implementująca interfejs [Json](./Json.md).  
Buduje abstrakcję nad tablicami JSON.

```cpp
class Array : public Json
```

Klasa zbudowana jest wokół `std::vector< JsonVariant >`.  
Zdecydowałem się zrezygnować tutaj z dziedziczenia (po `std::vector`), by interfejs publiczny tej klasy nie używał typu [JsonVariant](./JsonVariant.md).

### Konstruktory

```cpp
Array() = default;  
Array(const std::vector< std::shared_ptr< Json > >& vec);
Array(const Array& other);  
Array(Array&& other) noexcept;  
Array(std::shared_ptr< Allocator > alloc, PrimArray& prim);
```

Dostępne są następujące konstruktory:

- Domyślny (pusta tablica)
- `Array(vec)` – utworzy klasę zainicjowaną wskaźnikami z otrzymanego `vec`
- `Array(const Array& other)` – utworzy klasę pobierając wartość z `other`
- `Array(Array&& other)` – utworzy klasę pobierając wartość z tymczasowego `other`
- `Array(alloc, prim)` – konstruktor konwertujący typ prymitywny w abstrakcyjny; wszystkie elementy wskazywane przez typ prymitywny zostaną użyte do utworzenia `JsonVariant`. Później typ prymitywny i tablica wskaźników zostanie zwolniona

### API

#### Operatory

```cpp
Array& operator=(const Array& other);  
Array& operator=(Array&& other) noexcept;  
Array& operator=(const std::vector< std::shared_ptr< Json > >& vec);
```

Jeśli operator przypisania zostanie użyty wraz ze stałą referencją, to elementy zostaną skopiowane. Dla referencji tymczasowej klasy `std::vector` zostaną zamienione miejscami (referencja tymczasowa zostanie od razu usunięta, więc stary `std::vector` również).

W przypadku użycia operatora przypisania wraz wektorem wskaźników dane zawarte w `Array` zostaną usunięte, a wskaźniki zostaną skopiowane do pustego wektora.

---

```cpp
Json& operator[](std::size_t inx);
```

Tak jak w przypadku klasycznych tablic możliwe jest użycie operatora `[]` do wykonania dostępu do pól `Array`.

Jeśli pozycja `inx` nie znajduje się w wewnętrznym `std::vector` zostanie rzucony wyjątek `std::out_of_range`.

#### Funkcje

```cpp
std::size_t size() const;  
```

Pozwoli pobrać ilość elementów znajdujących się w `Array`.

---

```cpp
void push_back(Json& elem);  
void push_back(Json&& elem);  
void push_back(const std::shared_ptr< Json >& elem);  
```

Funkcje pozwalają dodać element na koniec tablicy.  
Możliwe jest przekazanie referencji na obiekt `Json` (wykonana zostanie kopia), referencji tymczasowe (brak kopii!) lub od razu wskaźnika na typ `Json`.

---

```cpp
void pop_back();
```

Pozwala usunąć ostatni element tablicy. Brak efektu przy pustej tablicy.

---

```cpp
void clear();
```

Pozwala usunąć wszystkie elementy tablicy.

---

```cpp
std::shared_ptr< Json >& getOwner(std::size_t inx);
```

Pozwala pobrać referencje na wskaźnik będący właścicielem `inx`-tego elementu.  
Używane do konwersji typów elementów już znajdujących się w tablicy za pomocą funkcji `Json::castTo`.

#### Iterator

```cpp
iterator begin();  
iterator end();
```

Klasa implementuje concept iteratora z użyciem klasy `ArrayIterator`.  
Udostępniony jest standardowy interfejs iteratora, w tym:

- `iterator(Array& arr, std::size_t inx = 0)` – konstruktor
- `Array& operator*()` – operator pobierania referencji na aktualny element
- `iterator& operator++()` – operator pozwalający przejść do następnego elementu

> **Nie** implementowany jest concept stałego iteratora.