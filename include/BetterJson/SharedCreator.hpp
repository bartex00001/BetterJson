#pragma once

#include <memory>

#include <BetterJson/Visitor.hpp>

namespace json
{

class SharedCreator : public Visitor
{
	std::shared_ptr< Json > shared;
	bool isMovable;

public:
	SharedCreator() = default;

	std::shared_ptr< Json > operator()(Json& json);
	std::shared_ptr< Json > operator()(Json&& json);

	void visit(Object& obj) override;
	void visit(Array& arr) override;
	void visit(String& str) override;
	void visit(Float& f) override;
	void visit(Int& i) override;
	void visit(Bool& b) override;
	void visit(Null& null) override;
};

}//namespace json
