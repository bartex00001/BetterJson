#include <iostream>
#include <unordered_map>

#include <BetterJson/json.hpp>

int main()
{
	json::Object obj;
	obj.emplace("abc", json::Int(2));
	obj["abc"].as< json::Int >() = 3;
	obj["key"];

	std::cout << obj;
}

