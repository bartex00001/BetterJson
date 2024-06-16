#pragma once

#include <BetterJson/JsonTypes/Null.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

template< Allocator TAllocator >
Null::Null(std::shared_ptr< TAllocator > alloc, PrimNull& pNull)
{
    alloc->free(&pNull);
}

void Null::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}