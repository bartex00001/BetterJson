#include <iostream>

#include <BetterJson/json.hpp>


void iterate(json::Array& arr)
{
    for(int i = 0; i < arr.size(); i++)
    {
        std::cout <<
            (long double)arr[i].as< json::Float >()
            << std::endl;
    }
}

int main()
{
    try
    {
        auto json = json::parse(json::FileBuffer("{\"key\":[1.0,2.0]}"));
        std::cout << "Parsed JSON" << std::endl;
        iterate((*json)["key"].as< json::Array >());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

