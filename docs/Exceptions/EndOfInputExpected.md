# EndOfInputExpected

Klasa dziedzicząca po `std::exception`.  
Używana do tworzenia wyjątków jeśli na końcu pliku występują dodatkowe znaki.

```cpp
class EndOfInputExpected : public std::exception
```

### Konstruktor

```cpp
EndOfInputExpected(File& buffer) noexcept;
```

Dostępny jest jeden konstruktor przyjmujący jako parametr [File](../Parser/File.md) z nieoczekiwanymi znakami (użyty do wygenerowania error-message).

## Przykład

```cpp
if(!isInputEnd)  
    throw EndOfInputExpected(file.get());
	// what(): Expected end of input, but fond:
	// 23      |     abc
```
