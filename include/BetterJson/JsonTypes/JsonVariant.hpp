#pragma once

#include <memory>
#include <optional>
#include <variant>

#include <BetterJson/Allocator.hpp>
#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/Prim.hpp>


namespace json
{

class JsonVariant
{
	std::variant< std::shared_ptr< Json >, std::reference_wrapper< PrimVariant > > json;
    std::optional< std::shared_ptr< DefaultAllocator > > allocator;

public:
    JsonVariant() = default;
	JsonVariant(PrimVariant& primVariant, std::shared_ptr< DefaultAllocator > alloc);
	JsonVariant(std::shared_ptr< Json > jsonType);

	std::shared_ptr< Json >& getRawJson();
	std::shared_ptr< Json > getJson();
};

}// namespace json
