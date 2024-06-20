# ObjKeyValuePair

Struktura danych reprezentująca parę *klucz* – *wartość* w obiektach JSON:

```cpp
struct ObjKeyValuePair  
{  
    char* key{};  
    PrimVariant* value{};  
};
```

> Klamry po nazwach pól oznaczają inicjalizację podstawowymi wartościami;  

Przechowuje ona:

- `key` – wskaźnik na tekst będący kluczem (zawsze właściciel tej pamięci)
- `value` – wskaźnik na wartość JSON – jedna ze struktur [PrimVariant](./PrimVariant.md) 

`value` jest wskaźnikiem by obiekt zawarty w `PrimVariant` mógł *usunąć się* bez usuwania `ObjKeyValuePair`.