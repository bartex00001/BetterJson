#pragma once

#include <BetterJson/Printer.hpp>


namespace json
{

Printer::Printer(unsigned indent)
    : indent(indent)
{}

std::string Printer::operator()(Json& json)
{
    buff.clear();
    json.accept(*this);
    return buff;
}

void Printer::printIndent()
{
    if(indent.has_value())
    {
        buff += '\n';
        for(unsigned i{}; i < level * indent.value(); i++)
            buff += ' ';
    }
    else
    {
        buff += '\n';
        for(unsigned i{}; i < level; i++)
            buff += '\t';
    }
}

void Printer::printMultilineObject(Object& obj)
{
    for(auto it: obj)
    {
        printIndent();
        buff += '"';
        buff += it.first;
        buff += '"';
        buff += ": ";
        it.second.accept(*this);

        buff += ',';
    }

    buff.pop_back();
}

void Printer::printMultilineArray(Array& arr)
{
    for(auto& elem: arr)
    {
        printIndent();
        elem.accept(*this);

        buff += ',';
    }

    buff.pop_back();
}


void Printer::visit(Object& obj)
{
    buff += "{";

    switch (obj.size())
    {
    case 0:
        buff += " ";
        break;
    default:
        level++;
        printMultilineObject(obj);
        level--;
        printIndent();
    }

    buff += "}";
}

void Printer::visit(Array& arr)
{
    buff += "[";

    switch (arr.size())
    {
    case 0:
        buff += " ";
        break;
    default:
        level++;
        printMultilineArray(arr);
        level--;
        printIndent();
    }

    buff += "]";
}

void Printer::visit(String& str)
{
    buff += '"';
    buff += str.value();
    buff += '"';
}

void Printer::visit(Float& f)
{
    buff += std::to_string(f.value());
}

void Printer::visit(Int& i)
{
    buff += std::to_string(i.value());
}

void Printer::visit(Bool& b)
{
    buff += b.value() ? "true" : "false";
}

void Printer::visit(Null& null)
{
    buff += "null";
}


std::ostream& operator<<(std::ostream& os, Json& json)
{
    return os << Printer(4)(json);
}

}