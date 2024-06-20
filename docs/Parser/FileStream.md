# FileStream

Klasa implementująca interfejs [File](./File.md).  
Buduje abstrakcję nad strumieniem wejściowym.

```cpp
class FileStream final : public File
```

### Konstruktory

```cpp
FileStream(const std::string& fileName);  
FileStream(std::istream& stream);
```

Dostępne są dwa konstruktory dla tej klasy:

- `FileStream(fileName)` – konstruktor otworzy plik o podanej nazwie i potraktuje go jako strumień wejściowy
- `FileStream(stream)` – użyty zostanie przekazany strumień

Jeśli użyty został konstruktor przyjmujący nazwę pliku, to strumień zostanie zamknięty przez destruktor klasy.