/* This example shows application creating a json object and writing it to the standard output;
 * The application will create an object mapping numbers to their dividers.
 */

#include <ranges>

#include <BetterJson/json.hpp>

constexpr int MAX_NUMBER{25};

std::vector< int > getDividers(int n)
{
	/* Only supported by the most modern compilers
	 * return std::views::iota(1, n)
	 * 	  | std::views::filter([&](int i){ return n % i == 0; })
	 * 	  | std::ranges::to< std::vector< int > >();
	 */

	std::vector< int > res;
	for(int i{1}; i <= n; i++) if(n % i == 0)
		res.push_back(i);

	return res;
}


int main()
{
	json::Object obj;

	for(int i{1}; i <= MAX_NUMBER; i++)
	{
		auto dividers{getDividers(i)};

		json::Array array;
		std::for_each(dividers.begin(), dividers.end(), [&](int n) {
			array.push_back(json::Int(n));
		});

		obj.emplace(
			std::to_string(i),
			std::move(array));
	}

	std::cout << json::Printer(4)(obj) << '\n';
}
