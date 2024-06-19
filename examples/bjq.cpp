/* bjq - program imitating part of a jq application: formatting and linting.
 * If the flag '-f' is passed into the application followed by file name then the json will be read form that file.
 * Otherwise stdin will be used
 */

#include <BetterJson/json.hpp>


void useStdin()
{
	auto json{json::Parser::parse(std::cin)};
	std::cout << *json;
}

void useFile(const std::string& fileName)
{
	auto file{json::FileStream(fileName)};
	auto json{json::Parser::parse(file)};
	std::cout << *json;
}

int main(int argc, char** argv)
{
	if(argc == 1)
		useStdin();
	else if(argc == 3 && std::strcmp(argv[1], "-i") == 0)
		useFile(argv[2]);
	else
	{
		std::cerr << "Invalid arguments\nexpected no arguments or '-i' followed by filename\n";
		exit(1);
	}
}
