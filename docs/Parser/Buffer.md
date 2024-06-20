# Buffer

Klasa implementująca interfejs [File](./File.md).  
Buduje abstrakcję nad buforem znaków.

```cpp
class Buffer final : public File
```

### Konstruktor

```cpp
Buffer(const char* str);
```

Dostępny jest jeden konstruktor przyjmujący wskaźnik na bufor znaków.  
Zawartość bufora nie zostanie zmieniona – w szczególności nie zostanie on usunięty.
