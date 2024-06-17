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

inline Null::Null(Null&)
{}

inline Null::Null(Null&&) noexcept
{}


inline void Null::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
