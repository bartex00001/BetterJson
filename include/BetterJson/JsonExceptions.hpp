#pragma once

#include <exception>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

class NameIdentifier;

class BadCast : public std::bad_cast
{
	std::string message;

	template< JsonSubclass TJson >
	static std::string getName();

	BadCast() = default;

public:
	template< JsonSubclass TJson >
	static BadCast create(Json& json);

	[[nodiscard]]
	const char* what() const noexcept override;
};


class NameIdentifier : public Visitor
{
	std::string name;

public:
	NameIdentifier() = default;

	std::string operator()(Json& json);
	std::string operator()(Json&& json);

	void visit(Object& obj) override;
	void visit(Array& arr) override;
	void visit(String& str) override;
	void visit(Float& f) override;
	void visit(Int& i) override;
	void visit(Bool& b) override;
	void visit(Null& null) override;
};

}//namespace json
