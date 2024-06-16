#pragma once

#include <optional>

#include <BetterJson/Visitor.hpp>


namespace json
{

class Printer : public Visitor
{
    std::optional< unsigned > indent{};
    std::string buff{};

    unsigned level{};

    void printIndent();

    void printMultilineObject(Object& obj);
    void printMultilineArray(Array& arr);

public:
    Printer() = default;
    Printer(unsigned indent);

    std::string operator()(Json& json);

    void visit(Object& obj) override;
    void visit(Array& arr) override;
    void visit(String& str) override;
    void visit(Float& f) override;
    void visit(Int& i) override;
    void visit(Bool& b) override;
    void visit(Null& null) override;
};

inline std::ostream& operator<<(std::ostream& os, Json& json);

}
