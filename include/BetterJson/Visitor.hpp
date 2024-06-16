#pragma once

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/Object.hpp>
#include <BetterJson/JsonTypes/Array.hpp>
#include <BetterJson/JsonTypes/Int.hpp>
#include <BetterJson/JsonTypes/Float.hpp>
#include <BetterJson/JsonTypes/String.hpp>
#include <BetterJson/JsonTypes/Bool.hpp>
#include <BetterJson/JsonTypes/Null.hpp>

namespace json
{

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

}