# Allocator

Concept definiujący oczekiwaną funkcjonalność od alokatora pamięci.

```cpp
template< typename T >  
concept Allocator
```

Wymaga on:

- Trywialnego konstruktora `T()`
- Konstruktora przyjmującego wartości tymczasowe `T(T&&)`
- Nadpisanego operatora `=` dla wartości tymczasowych
- Istnienia funkcji `malloc: size_t -> void*` – funkcja alokująca pamięć
- Istnienia funkcji `realloc: void* -> size_t -> size_t -> void*` – funkcja zmieniająca rozmiar alokowanej pamięci
- Istnienia statycznej funkcji `free: void* -> ()`

## Implementacje

Biblioteka definiuje dwie klasy implementujące ten interfejs:

- [CStdAllocator](./CStdAllocator.md)
- [MemoryPool](./MemoryPool.md)

#### Implementacje?

W C++ nie można *jawnie* implementować concept, jedynie *przypadkowo spełniać jego wymagania*.
By wymusić implementowanie tego concept przez wyżej wymienione klasy w pliku zdefiniowane są odpowiednie asercje:

```cpp
static_assert(Allocator< CStdAllocator >);  
static_assert(Allocator< MemoryPool< CStdAllocator > >);
```

Przez to nie poprawna implementacja interfejsu będzie skutkować błędem kompilacji.

## Default Allocator

Niestety użycie concept okazało się nie być dobrym pomysłem