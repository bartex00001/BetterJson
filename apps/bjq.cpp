#include <iostream>
#include <unordered_map>

#include <BetterJson/json.hpp>


struct Vector : json::JSON_BASE
{
	JSON(int, x)
	//JSON(int, y)
	//JSON_OPT(std::string, id);
};

int main()
{
	try
	{
		auto json = json::Parser::parse(json::FileStream(std::cin));
		Vector vec(*json);
	}
	catch(const json::BadCast& badCast)
	{
		std::cerr << badCast.what();
	}
}
