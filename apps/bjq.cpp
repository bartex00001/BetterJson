#include <iostream>
#include <unordered_map>

#include <BetterJson/json.hpp>


int main()
{
	auto json{json::Parser<>::parse(std::cin)};
	std::cout << *json;
}
