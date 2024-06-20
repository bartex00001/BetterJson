# PrimInt

Struktura przechowująca liczby całkowite JSON:

```cpp
struct PrimInt  
{  
    TypeId id;  
    long long value;  
};
```

Przechowuje ona:

- `id` – identyfikator typu
- `value` – wartość liczby

> W przyszłości (gdy zostaną wprowadzone do standardu) będzie można zmienić `value` na wskaźnik na liczbę n-bitową