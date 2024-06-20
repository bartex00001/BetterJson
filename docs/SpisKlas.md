# Spis Klas

Poniżej znajduje się spis wszystkich klas projektu.
Każda klasa posiada krótki opis – pełny znajduje się w *pliku klasy*.

Wszystkie klasy wymienione w tym pliku znajdują się w `namespace json`.

## Table of Contents
- [Prim Types](#prim-types)
- [Json Types](#json-types)
- [Allocators](#allocators)
- [Visitors](#visitors)
- [Exceptions](#exceptions)
- [Base Json](#base-json)

## Prim Types

> Prymitywne typy generowane przez parser

- [PrimVariant](./PrimTypes/PrimVariant.md) – unia przechowująca jeden z prymitywnych typów
	- [PrimObject](./PrimTypes/PrimObject.md) – prymitywny typ reprezentujący obiekt w JSON
		- [ObjKeyValuePair](./PrimTypes/ObjKeyValuePair.md) – struktura przechowująca klucz (tekst) i wskaźnik na wartość
	- [PrimArray](./PrimTypes/PrimArray.md) – prymitywny typ reprezentujący tablicę w JSON
	- [PrimString](./PrimTypes/PrimString.md) – prymitywny typ reprezentujący tekst w JSON
	- [PrimInt](./PrimTypes/PrimInt) – prymitywny typ reprezentujący liczby całkowitą w JSON
	- [PrimFloat](./PrimTypes/PrimFloat.md) – prymitywny typ reprezentujący liczby zmiennoprzecinkowe w JSON
	- [PrimBool](./PrimTypes/PrimBool.md) – prymitywny typ reprezentujący boolean w JSON
	- [PrimNull](./PrimTypes/PrimNull.md) – prymitywny typ reprezentujący null w JSON

## Json Types

> Klasy budujące abstrakcję nad wartościami JSON

- [Json](./JsonTypes/Json.md) – wirtualna (abstrakcyjna) klasa bazowa dla typów reprezentujących wartości JSON
	- [Object](./JsonTypes/Object.md) – klasa reprezentująca obiekt w JSON
	- [Array](./JsonTypes/Array.md) – klasa reprezentująca tablicę w JSON
	- [String](./JsonTypes/String.md) – klasa reprezentująca tekst w JSON
	- [Int](./JsonTypes/Int.md) – klasa reprezentująca liczby całkowite w JSON
	- [Float](./JsonTypes/Float.md) – klasa reprezentująca liczby zmiennoprzecinkowe w JSON
	- [Bool](./JsonTypes/Bool) – klasa reprezentująca boolean w JSON
	- [Null](./JsonTypes/Null.md) – klasa reprezentująca null w JSON
- [JsonVariant](JsonVariant.md) – klasa przechowująca prymitywną bądź abstrakcyjny typ JSON

## Allocators

> Klasy pozwalające na zarządzanie pamięcią

- [Allocator](./Allocators/Allocator.md) – concept (interfejs)
	- [CStdAllocator](./Allocators/CStdAllocator.md) – abstrakcja nad funkcjami biblioteki standardowej C
	- [MemoryPool](./Allocators/MemoryPool.md) – allocator ze strategią

## Visitors

> Klasy wykorzystujące pattern *visitor*

- [Visitor](./Visitors/Visitor.md) – wirtualna (abstrakcyjna) klasa
	- [Printer](./Visitors/Printer.md) – funktor konwertujący JSON do reprezentacji tekstowej
	- [SharedCreator](./Visitors/SharedCreator.md) – funktor tworzący obiekty `std::shared_ptr` dla typów abstrakcyjnych JSON
	- [NameIdentifier](./Visitors/NameIdentifier.md) – funktor zwracający nazwę typu JSON

## Parser

>  Klasy wykorzystywane do parsowania JSON

- [Parser](./Parser/Parser.md) – klasa odpowiedzialna za parsowanie JSON
- [File](./Parser/File.md) – interfejs tworzący abstrakcję nad plikiem (napisem)
	- [Buffer](./Parser/Buffer.md) – implementacja `File` dla bufora danych
	- [FileStream](./Parser/FileStream.md) – implementacja `File` dla plików/strumieni

## Exceptions

> Klasy reprezentujące wyjątki – dziedziczące po `std::exception`

- [BadCast](./Exceptions/BadCast.md) – wyjątek informujący o nieudanym cast
- [SyntaxError](./Exceptions/SyntaxError.md) – wyjątek informujący o błędnej składni
- [EndOfInputExpected](./Exceptions/EndOfInputExpected) – wyjątek informujący o nadmiernych znakach na końcu wejścia

## Base Json

> Klasa pozwalająca na tworzenie struktur danych inicjalizowalnych typami JSON

- [BaseJson](./BaseJson/BaseJson.md) – klasa bazowa dla struktur danych
