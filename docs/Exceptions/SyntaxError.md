# Syntax Error

Klasa dziedzicząca po `std::exception`.  
Używana przez [Parser](../Parser/Parser.md) do tworzenia wyjątków w przypadku napotkania błędów składniowych.

```cpp
class SyntaxError : public std::exception
```

### Konstruktory

```cpp
static SyntaxError unexpectedCharactrersWhenParsing(File& buffer, char c, const std::string& type);  
static SyntaxError expectedCharacters(File& buffer, const std::string& chars, const std::string& info);  
static SyntaxError constOverflow(File& buffer);
```

*Prawdziwy* konstruktor jest prywatny.  
Do tworzenia wyjątków należy użyć jednej z metod statycznych:

- `unexpectedCharactrersWhenParsing` – znaleziono nieoczekiwany znak
	- `buffer` – [File](../Parser/File.md) w którym doszło do wyjątku
	- `c` – niespodziewany znak 
	- `type` – typ wartości JSON, który był parsowany
- `expectedCharacters` – nie znaleziono znaku(ów)
	- `buffer` – [File](../Parser/File.md) w którym doszło do wyjątku
	- `chars` – oczekiwane znaki
	- `info` – dodatkowa informacja
- `constOverflow`
	- `buffer` – [File](../Parser/File.md) w którym doszło do wyjątku

## Przykład

```cpp
if(!isTrue)  
    throw SyntaxError::unexpectedCharactrersWhenParsing(file, file.peek(), "true");
	// what(): Started parsing 'true' but found unexpected character: 'k' at line
	// 23    | "someVal": trke,
```

```cpp
if(!file.consume('['))  
    throw SyntaxError::expectedCharacters(file, "[", "at the start of an Array");

	// what(): Expected symbol '[' at the start of an array at line
	// 67    | 123421
```

```cpp
if(inx >= buffSize-1)  
    throw SyntaxError::constOverflow(file);
    // what(): Constant too large (will overflow) at line
    // 17     | 42398409323746137824760812342304732401723847829347043092819,
```