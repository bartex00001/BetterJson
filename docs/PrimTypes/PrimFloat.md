# PrimFloat

Struktura reprezentująca liczby zmiennoprzecinkowe JSON:

```cpp
struct PrimFloat  
{  
    TypeId id;  
    double value;  
};
```

Przechowuje ona:

- `id` – identyfikator typu
- `value` – wartość liczby

> Nie został użyty typ `long double`, ponieważ wymaga on alignment na poziomie `16` bajtów, co zwiększyło by rozmiar struktury do `32` bajtów