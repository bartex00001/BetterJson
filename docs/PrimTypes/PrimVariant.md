# Prim Variant

Jest to unia przechowująca jedną z prymitywnych struktur danych:

- [PrimNull](./PrimNull.md)
- [PrimObject](./PrimObject.md)
- [PrimArray](./PrimArray.md)
- [PrimString](./PrimString.md)
- [PrimInt](./PrimInt)
- [PrimFloat](./PrimFloat.md)
- [PrimBool](./PrimBool.md)

```cpp
union PrimVariant  
{  
    PrimNull pNull{.id = PRIM_NULL_ID};  
    PrimArray pArray;  
    PrimObject pObject;  
    PrimBool pBool;  
    PrimFloat pFloat;  
    PrimInt pInt;  
    PrimString pString;  
};
```

Jeśli `PrimVariant` nie zostanie zainicjowany wartością, to będzie przechowywać typ `PrimNull`.

Jest to typ generowany przez parser – jego tworzenie jest trywialne i zajmuje mało pamięci.  
Ze względu na nieprzyjemny interfejs unia nie jest nigdy widoczna dla użytkownika biblioteki.

### Rozpoznawanie Typów

Każda prymitywna struktura danych posiada jako pierwsze w kolejności pole typu `TypeId` – `id` (alias dla `uint8_t`). W szczególności `PrimNull` posiada tylko to pole.

By wyznaczyć typ przechowywanego obiektu wystarczy porównać wartość przechowywaną w tym polu z ustalonymi wartościami kodującymi.

### Rozmiar Struktury

Każda struktura zawarta w `PrimVariant` zajmuje co najwyżej `24` bajty z wymogiem alignment `8` bajtów – unia zajmuje `24` bajty i może być ustawiana *po sobie*.

Technicznym minimum na wielkość struktury było by `16` bajtów, ale wiązało by się to z ograniczeniem możliwej wielkości tablic i obiektów JSON.