#pragma once

#include <variant>
#include <memory>

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

class JsonVariant
{
	std::variant< std::shared_ptr< Json >, std::reference_wrapper< PrimVariant > > json;
    std::optional< std::shared_ptr< DEFAULT_ALLOCATOR > > allocator;

public:
    JsonVariant() = default;

	JsonVariant(PrimVariant& primVariant, std::shared_ptr< DEFAULT_ALLOCATOR > alloc)
        : json(primVariant),
          allocator(alloc)
    {}

	JsonVariant(std::shared_ptr< Json > jsonType)
        : json(jsonType)
    {}

	std::shared_ptr< Json > getJson();
};

}// namespace json


