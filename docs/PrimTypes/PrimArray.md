# PrimArray

Struktura reprezentująca tablice w JSON:

```cpp
struct PrimArray  
{  
    TypeId id;  
    std::uint32_t size;  
    std::uint32_t capacity;  
    union PrimVariant** elements;  
};
```

Przechowuje ona:

- `id` – identyfikator typu
- `size` – liczba elementów znajdujących się w obiekcie
- `capacity` – liczba zarezerwowanych bajtów na umieszczanie kolejnych wartości
- `elements` – tablica wskaźników na [wartości JSON](./PrimVariant.md)

`elements` jest tablicą wskaźników, by poszczególne elementy mogły *usunąć siebie* bez naruszania pozostałych elementów.

> Jeśli typy `size` i `capacity` zmienione zostały by na `std::uint16_t`, to wielkość struktury została by zmniejszona do `16` bajtów (z `24`)