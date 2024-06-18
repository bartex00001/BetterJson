#include <iostream>
#include <unordered_map>

#include <BetterJson/json.hpp>


int main()
{
	json::Object obj;
	obj.emplace("abc", json::Int(123));
	obj["abc"] = json::Int(321);

	std::cout << obj;
}
