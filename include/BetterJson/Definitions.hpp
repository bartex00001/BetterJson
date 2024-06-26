#pragma once

#ifndef BETTER_JSON_CHUNK_SIZE
#define BETTER_JSON_CHUNK_SIZE 4096
#endif

#if BETTER_JSON_CHUNK_SIZE < 128
#error "BETTER_JSON_CHUNK_SIZE must be at least 128 bytes long"
#endif

#ifndef BETTER_JSON_LINE_BUFFER_SIZE
#define BETTER_JSON_LINE_BUFFER_SIZE 128
#endif

#ifndef BETTER_JSON_ARRAY_DEFAULT_CAPACITY
#define BETTER_JSON_ARRAY_DEFAULT_CAPACITY 8
#endif


#include <BetterJson/MemoryPool.hpp>
#include <BetterJson/CStdAllocator.hpp>

namespace json
{
using DefaultAllocator = MemoryPool< CStdAllocator >;
}
