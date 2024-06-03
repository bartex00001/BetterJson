#include <iostream>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Allocator.hpp>
#include <BetterJson/CStdAllocator.hpp>
#include <BetterJson/MemoryPool.hpp>

int main()
{
	json::MemoryPool<json::CStdAllocator> csa;
	int* i{static_cast<int*>(csa.malloc(4))};

	*i = 10;
	std::cout << *i;

	csa.free(i);
}
