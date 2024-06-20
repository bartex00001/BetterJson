# Visitor

Klasa abstrakcyjna (interfejs) zawierający metody *wizytujące* dla każdej podklasy [Json](../JsonTypes/Json.md):

```cpp
class Visitor  
{  
public:  
    virtual void visit(Object& obj) = 0;  
    virtual void visit(Array& arr) = 0;  
    virtual void visit(String& str) = 0;  
    virtual void visit(Float& f) = 0;  
    virtual void visit(Int& i) = 0;  
    virtual void visit(Bool& b) = 0;  
    virtual void visit(Null& null) = 0;  
  
    virtual ~Visitor() = default;  
};
```

Wirtualny destruktor wymagany jest, by możliwe było usuwanie klas dziedziczących bez wiedzy o ich typie.

## Implementacje

Klasy dziedziczące po `Visitor`:

- [Printer](./Printer.md)
- [NameIdentifier](NameIdentifier.md)
- [SharedCreator](./SharedCreator.md)
