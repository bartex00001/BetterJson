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
	T& as();

    virtual void accept(class Visitor& visitor) = 0;
};

}// namespace json
