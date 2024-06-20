# Allocator

Klasa abstrakcyjna (interfejs) definiująca oczekiwaną funkcjonalność od alokatora pamięci.

```cpp
class Allocator  
{  
public:  
    virtual void* malloc(std::size_t n) = 0;  
    virtual void* realloc(void* addr, std::size_t oldSize, std::size_t newSize) = 0;  
    virtual void free(void* addr) noexcept = 0;  
  
    virtual ~Allocator() = default;  
};
```

Interfejs wymaga istnienia funkcji:

- `malloc: size_t -> void*` – funkcja alokująca pamięć
- `realloc: void* -> size_t -> size_t -> void*` – funkcja zmieniająca rozmiar alokowanej pamięci
- `free: void* -> ()` – funkcja zwalniająca pamięć

## Implementacje

Biblioteka definiuje dwie klasy implementujące ten interfejs:

- [CStdAllocator](./CStdAllocator.md)
- [MemoryPool](./MemoryPool.md)

## Default Allocator

Jako podstawowy alokator (wybierany, gdy specjalny nie zostanie wybrany) biblioteka definiuje: `MemoryPool< CStdAllocator >` – alokator ze strategią *memory pool* korzystający z funkcji biblioteki C do wykonywania poszczególnych alokacji.