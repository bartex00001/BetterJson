#pragma once

#include <BetterJson/JsonTypes/Null.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

template< Allocator TAllocator >
Null::Null(std::shared_ptr< TAllocator > alloc, PrimNull& pNull)
{
    alloc->free(&pNull);
}

}