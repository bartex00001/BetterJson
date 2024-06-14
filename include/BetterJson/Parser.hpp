#pragma once

#include <BetterJson/Prim.hpp>
#include <BetterJson/Allocator.hpp>


namespace json::parser
{

PrimVariant* parseObject(Allocator auto& alloc, char*& buffer);
PrimVariant* parseArray(Allocator auto& alloc, char*& buffer);
PrimVariant* parseString(Allocator auto& alloc, char*& buffer);
PrimVariant* parseInt(Allocator auto& alloc, char*& buffer);
PrimVariant* parseFloat(Allocator auto& alloc, char*& buffer);
PrimVariant* parseBool(Allocator auto& alloc, char*& buffer);
PrimVariant* parseNull(Allocator auto& alloc, char*& buffer);

}

#include <BetterJson/Parser.tpp>