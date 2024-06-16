#pragma once

#include <BetterJson/JsonTypes/Json.hpp>
#include <BetterJson/JsonTypes/Object.hpp>
#include <BetterJson/JsonTypes/Array.hpp>
#include <BetterJson/JsonTypes/Int.hpp>
#include <BetterJson/JsonTypes/Float.hpp>
#include <BetterJson/JsonTypes/String.hpp>
#include <BetterJson/JsonTypes/Bool.hpp>
#include <BetterJson/JsonTypes/Null.hpp>

#include <BetterJson/File.hpp>
#include <BetterJson/Parser.hpp>

#include <BetterJson/Printer.hpp>

#include <BetterJson/Implementations/JsonVariant.tpp>
#include <BetterJson/Implementations/Json.tpp>

#include <BetterJson/Implementations/Exceptions.tpp>

#include <BetterJson/Implementations/File.tpp>
#include <BetterJson/Implementations/Parser.tpp>

#include <BetterJson/Implementations/Object.tpp>
#include <BetterJson/Implementations/Array.tpp>
#include <BetterJson/Implementations/Int.tpp>
#include <BetterJson/Implementations/Float.tpp>
#include <BetterJson/Implementations/String.tpp>
#include <BetterJson/Implementations/Bool.tpp>
#include <BetterJson/Implementations/Null.tpp>


namespace json
{

inline std::shared_ptr< Json > parse(File& file)
{
    auto allocator{std::make_shared< DEFAULT_ALLOCATOR >(DEFAULT_ALLOCATOR{})};
    return std::make_shared< Object >(
        allocator,
        Parser<>(*allocator, file)()
    );
}

inline std::shared_ptr< Json > parse(File&& file)
{
    auto allocator{std::make_shared< DEFAULT_ALLOCATOR >(DEFAULT_ALLOCATOR{})};
    return std::make_shared< Object >(
        allocator,
        Parser<>(*allocator, file)()
    );
}

}