#pragma once


namespace json
{

class Json
{
    Json(const Json& other) = delete;
    Json(Json&& other) = delete;
    Json& operator=(const Json& other) = delete;
    Json& operator=(Json&& other) = delete;

protected:
	Json() = default;

public:
	virtual ~Json() = default;

	template< typename T >
	requires std::is_base_of_v< Json, T >
	auto as() -> T&;

	template< typename T >
	requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)
	auto operator=(T& other) -> T&;

	template< typename T >
	requires std::is_base_of_v< Json, T > && (!std::is_same_v< Json, T >)
	auto operator=(T&& other) -> T&;

    virtual void accept(class Visitor& visitor) = 0;
};

template< typename T >
concept JsonSubclass = std::is_base_of_v< Json, T > && !std::is_same_v< Json, T >;

}// namespace json
