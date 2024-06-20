# BaseJson

Klasa pozwalająca na tworzenie struktur danych inicjalizowalnych podklasami [Json](../JsonTypes/Json.md).

> Jest to eksperyment sprawdzający na ile pozwala system typów C++  
> Niestety na niezbyt wiele...

```cpp
class JSON_BASE
```

**Uwaga**: klasa nie jest abstrakcyjna, ale nie powinny być tworzone jej instancje (nie będzie to błędne, ale pozbawione sensu). Niestety C++ nie pozwala na dziedziczenie konstruktorów od klas abstrakcyjnych, więc jest to jedyne wyjście.

### Pola Json

Dla tej klasy zdefiniowane zostały trzy makra do definiowania elementów struktury, które powinny być wczytane z obiektu `Json`:

- `JSON(type, name)` – element typu *podstawowego* C++ o nazwie `name`
- `JSON_VEC(vType, name)` – element typu `std::vector< vType >` o nazwie `name`
- `JSON_OPT(vType, name)` – elementy typu `std::optional< vType >` o nazwie `name`
	- Jeśli `json` nie zawiera żadnego klucza dla `name`, to `optional` pozostanie pusty

#### Ograniczenia

- Niepoprawne użycie makra wygeneruje bardzo brzydki błąd
- Możliwe jest inicjalizowanie tylko typów podstawowych
	- Jeśli funkcja C++ otrzyma jako template typ złożony, np.: `std::vector< vType >`, to nie jest możliwe użycie wewnętrznego typu `vType` jako parametru do innych template (pomimo istnienia `std::vector< ... >::value_type`)


### Konstruktory

```cpp
JSON_BASE() = default;  
JSON_BASE(Json& json);
```

- konstruktor domyślny ustawi wartości *pól JSON* na wartości domyślne
- konstruktor przyjmujący typ `Json` – ustawi wartości *pol json* na `json[nazwa]`.

### Przykład

```cpp
struct Example : json::JSON_BASE // struct domyślnie dziedziczy publicznie
{
	JSON(int, x)
	JSON(int, y)

	JSON(std::string, name)

	JSON_VEC(float, intervals) // std::vector< float > intervals;

	JSON_OPT(int, scale) // std::optional< float > scale

	// Pole nie-wczytywane przez z obiektów Json
	SomeStruct someName;

	// Możliwe jest tworzenie funkcji i innych konstruktorów
	Example(SomeStruct);
	int foo();
};

// w main()

Json& json{...};
Example e(json);

std::cout << e.x; // zmienne są dostępne pod podanymi nazwami
```

