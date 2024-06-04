#include <iostream>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Allocator.hpp>
#include <BetterJson/CStdAllocator.hpp>
#include <BetterJson/MemoryPool.hpp>

int main()
{
	json::MemoryPool< json::CStdAllocator > cse;

	int* i = reinterpret_cast< int* > (cse.malloc(4));
	*i = 5;

	std::cout << *i;

	cse.free(i);
}
