#include <iostream>
#include <unordered_map>

#include <BetterJson/json.hpp>


struct Point : json::JSON_BASE
{
	JSON(int, x)
	JSON(int, y)

	JSON(float, length)

	JSON(std::string, name);

	JSON_VEC(long, values);

	JSON_OPT(int, sign);
};

int main()
{
	json::Object obj;
	obj.emplace("x", json::Int(2));
	obj.emplace("y", json::Int(3));
	obj.emplace("length", json::Float(123.5));
	obj.emplace("name", json::String("hello there"));
	obj.emplace("sign", json::Int(1223));

	json::Array arr;
	arr.push_back(json::Int(123));
	arr.push_back(json::Int(321));

	obj.emplace("values", arr);

	Point p(obj);

	Point p2{};

	std::cout
	<< p.x << "\n"
	<< p.y << "\n"
	<< p.length << "\n"
	<< p.name << "\n"
	<< p.sign.value() << '\n';


	for(auto it: p.values)
		std::cout << it << " ";
}
