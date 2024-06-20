# PrimString

Struktura przechowująca wartość tekstową JSON:

```cpp
struct PrimString  
{  
    TypeId id;  
    bool owner;  
    char* str;  
};
```

Przechowuje ona:

- `id` – identyfikator typu
- `owner` – informację, czy struktura jest właścicielem przechowywanego tekstu
- `str` – napis
