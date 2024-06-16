#include <iostream>

#include <BetterJson/json.hpp>



int main()
{
    try
    {
        auto json = json::parse(json::FileStream(std::cin));
        std::cout << *json << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

