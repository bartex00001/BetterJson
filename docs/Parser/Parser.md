# Parser

Klasa pozwalająca na parsowanie danych JSON przekazanych za pomocą interfejsu [File](./File.md).
Możliwa jest parametryzacja tej klasy za pomocą alokatora.

```cpp
template< typename TAllocator = DefaultAllocator >  
    requires std::is_base_of_v< Allocator, TAllocator >  
class Parser
```

## Użycie

```cpp
static std::shared_ptr< Json > parse(File& file);  
static std::shared_ptr< Json > parse(File&& file);  
static std::shared_ptr< Json > parse(const std::string& str);  
static std::shared_ptr< Json > parse(std::istream& stream);
```

Klasa nie definiuje publicznych konstruktorów.  
W zamian dostępne są funkcje statyczne:

- `parse(File&)` – parsowanie z użyciem klasy `File`
- `parse(File&&)` – umożliwienie parsowania tymczasowych obiektów `File`
- `parse(const std::string& str)` – parsowanie bufora `str`; skrót od tworzenia klasy `Buffer` i przekazywania jej do innej wersji metody `parse`
- `parse(std::istream& stream)` – parsowanie strumienia `stream`; skrót od tworzenia klasy `FileStream` i przekazywania jej do innej wersji metody `parse`

#### Excaptions

Każda z wyżej wymienionych funkcji może rzucić jeden z następujących wyjątków:

- [SyntaxError](../Exceptions/SyntaxError.md)
- [EndOfInputExpected](../Exceptions/EndOfInputExpected.md)

## Przykład

```cpp
// Parsowanie strumienia wejściowego przy użyciu podstawowego alokatora
auto json{json::Parser<>::parse(std::cin)};

// Parsowanie zawartości "some.json" używając 'MyCustomAllocator'
auto file{json::FileStream("some.json")};
auto json{json::Parser< MyCustomAllocator >::parse(file)};
```


## Hermetyzacja

Wewnętrznie parser korzysta z [typów prymitywnych](../PrimTypes/PrimVariant.md) operując na surowych wskaźnikach i uniach.  
Użytkownik nie powinien mieć dostępu do tych części biblioteki, stąd decyzja, by funkcjonalność parsera była dostępna tylko przy użyciu prostych w obsłudze funkcji statycznych.