# SharedCreator

Klasa implementująca interfejs [Visitor](./Visitor.md).  
Działa jak funktor pozwalający na tworzenie obiektów typu `std::shared_ptr< Json >` pamiętających oryginalny typ każdej podklasy [Json](../JsonTypes/Json.md).

```cpp
class SharedCreator : public Visitor
```

### Konstruktor

```cpp
SharedCreator() = default;
```

Dostępny jest tylko konstruktor domyślny.

### Operator Funkcyjny

```cpp
std::shared_ptr< Json > operator()(Json& json);  
std::shared_ptr< Json > operator()(Json&& json);
```

Dostępne są dwa warianty operatora funkcyjnego:

- `operator()(Json& json)` – zwrócony zostanie wskaźnik na kopię `json`
- `operator()(Json&& json)` – zwrócony zostanie wskaźnik na `json`
\
## Przykład

```cpp
// Dla json: Json& utworzy shared_ptr kopiując zawartość json
auto sharedJson{ SharedCreator()(json) };

// Dla json: Json& utorzy shared_ptr przenosząc zawartość json w nowe miejsce
// Nie należy dalej używać nazwy json, bo jej dane zostały zabrane
auto sameJson{ SharedCreator()(std::move(json)) };
```