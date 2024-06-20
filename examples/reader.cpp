/* This example shows application reading a json 'vectors.json' consisting of an array of objects.
 * Each object is a Vector; The application wil calculate and print an average length of all vectors.
 */

#include <cmath>

#include <BetterJson/json.hpp>

#define FILE_NAME "vectors.json"


struct Vector : json::JSON_BASE
{
	JSON(double, x);
	JSON(double, y);

	[[nodiscard]]
	double getLength() const
	{
		return std::sqrt(x*x + y*y);
	}
};

int main()
{
	auto file{json::FileStream(FILE_NAME)};
	auto json{json::Parser<>::parse(file)};

	double avg{};
	for(auto& obj: json->as< json::Array >())
	{
		Vector vec(obj);
		avg += vec.getLength();
	}

	avg /= json->as< json::Array >().size();
	std::cout << avg << '\n';
}
