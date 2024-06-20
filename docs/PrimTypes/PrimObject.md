# PrimObject

Struktura reprezentująca obiekt JSON:

```cpp
struct PrimObject  
{  
    TypeId id;  
    std::uint32_t size;  
    std::uint32_t capacity;  
    struct ObjKeyValuePair** elements;  
};
```

Przechowuje ona:

- `id` – identyfikator typu
- `size` – liczba elementów znajdujących się w obiekcie
- `capacity` – liczba zarezerwowanych bajtów na umieszczanie kolejnych wartości
- `elements` – tablica wskaźników na [elementy obiektu](./ObjKeyValuePair.md)

`elements` jest tablicą wskaźników, a nie *po prostu* tablicą typów `ObjKeyValuePair`, ponieważ taką tablicę można usuną jedynie posiadając wskaźnik na jej pierwszy element.  
Taka implementacja wprowadziła by dodatkowe zależności, gdzie obiekt musiałby pamiętać, czy może zwolnić pamięć, którą zajmuje.

Ta implementacja jest prostsza – każdy obiekt odpowiedzialny jest za zwolnienie swojej pamięci.

> Jeśli typy `size` i `capacity` zmienione zostały by na `std::uint16_t`, to wielkość struktury została by zmniejszona do `16` bajtów (z `24`)