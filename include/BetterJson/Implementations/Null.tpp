#pragma once

#include <BetterJson/JsonTypes/Null.hpp>
#include <BetterJson/Prim.hpp>
#include <BetterJson/Visitor.hpp>


namespace json
{

Null::Null(std::shared_ptr< Allocator > alloc, PrimNull& pNull)
{
    alloc->free(&pNull);
}

inline Null::Null(const Null&)
{}

inline Null::Null(Null&&) noexcept
{}


inline void Null::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

}//namespace json
