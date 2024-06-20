# File

Klasa abstrakcyjna (interfejs) definiujący abstrakcję nad danymi do parsowania:

```cpp
class File {  
public:    
    virtual char peek() const = 0;  
    virtual char get() = 0;  
    bool consume(char expected);  
  
    virtual std::size_t getLineNumber() const = 0;  
    virtual std::string getLine() = 0;  
    
    virtual ~File() = default;
};
```

Interfejs wymaga istnienia funkcji:

- `char peek()` – pobranie ostatniego znaku
- `char get()` – pobranie ostatniego znaku i przesunięcie o jeden do przodu
- `bool consume(char expected)` – sprawdza czy ostatni znak równy jest `expected`, jeśli:
	- tak – zwraca true i przesuwa kursor o jeden do przodu
	- nie – zwraca false
- `std::size_t getLineNumber()` – zwraca numer linii
- `std::string getLine()` – zwraca ostatnią linię

> Funkcja `consume` jest zaimplementowana już dla klasy `File`.

## Implementacje

Biblioteka definiuje dwie klasy implementujące ten interfejs:

- [Buffer](./Buffer.md)
- [FileStream](./FileStream.md)
