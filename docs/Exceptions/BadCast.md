# BadCast

Klasa dziedzicząca po `std::bad_cast` (które dziedziczy po `std::exception`).  
Używana do tworzenia wyjątków w przypadku nieudanego cast.

```cpp
class BadCast : public std::bad_cast
```

### Konstruktor

```cpp
template< JsonSubclass TJson >  
static BadCast create(Json& json);
```

Obiekt można utworzyć tylko korzystając ze statycznej metody `create` – konstruktor domyślny jest ustawiony jako prywatny.

Funkcja create jako parametr przyjmie obiekt, który próbowaliśmy castować i typ do którego chcieliśmy wykonać cast.  
Użyje ona [NameIdentifier](../Visitors/NameIdentifier.md), by poznać typ `json`, a nazwa typu `TJson` zostanie utworzona za pomocą pomocniczych, prywatnych metod statycznych.

## Przykład

```cpp
try  
{  
	// Dynamic cast musi być do wskaźnika bądź referencji
    return dynamic_cast< T& >(json);  
}  
catch(const std::bad_cast& badCast [[maybe_unused]])  
{  
    throw BadCast::create< T >(json);
    // what(): Cannot cast 'json::Null' to 'json::Array'
}
```
