# MemoryPool

Klasa implementująca interfejs [Allocator](./Allocator.md).  
Będzie alokować pamięć używając strategii *memory pool*.

```cpp
template< typename TAllocator >  
    requires std::is_base_of_v< Allocator, TAllocator >  
class MemoryPool : public Allocator
```

`MemoryPool` nie będzie wykonywać alokacji pamięci – będzie decydować jakie powinny zostać wykonane. Oczekuje, że instancja klasy przekazanego typu `TAllocator`, która również implementuje interfejs `Allocator` wykona alokacje.

> W szczególności możliwe jest przekazanie `TAllocator = MemoryPool`, ale na końcu takiej rekurencji będzie musiała znaleźć się w końcu inna klasa implementująca `Allocator`

### Konstruktor

Dostępny jest konstruktor domyślny.

## Strategia

Klasa implementuje prostą strategię *memory pool* – pamięć będzie zajmowana w blokach o wielkości możliwej do ustalenia definiując `BETTER_JSON_CHUNK_SIZE` (podstawową wartością jest `4096`).

#### Alokacja Elementu

- Czy element zmieści się w ostatnim bloku?
	- Tak -> adres po ostatnim zajętym i przesuń licznik użytych bajtów
	- Nie -> alokuj `max(BETTER_JSON_CHUNK_SIZE, n)` bajtów i zwróć na nie wskaźnik

#### Zmiana Rozmiaru Elementu

Warunki sprawdzane są w wymienionej kolejności, jeśli któryś jest spełniony, to wykonane zostanie działanie i funkcja zwróci nowy adres.

- Adres elementu jest pusty? -> wykonaj alokację
- Nowy rozmiar jest nie większy niż stary? -> jeśli jest to ostatni element w ostatnim bloku, to zmniejsz jego zajęcie
- Jest ostatnim elementem i zmieści się w bloku? -> zwiększ zajęcie bloku zajęcie bloku
- Jest dużym elementem i ostatnim w ostatnim bloku? -> zmień rozmiar bloku
- Alokuj nową pamięć (używając strategii alokacji) i skopiuj tam zawarte tu dane

#### Zwalnianie Pamięci

Pamięć nie jest zwalniana przy wywołaniach do funkcji `free`.  
Cała alokowana pamięć zostanie zwolniona dopiero gdy wykonany zostanie destruktor `MemoryPool`.