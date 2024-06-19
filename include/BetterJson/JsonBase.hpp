#pragma once


namespace json
{

class JSON_BASE
{
protected:
    std::optional< std::reference_wrapper< Json > > json;

    template< typename T >
    requires std::is_integral_v< T >
    static auto retrieve(Json& j) -> T;

    template< typename T >
    requires std::is_floating_point_v< T >
    static auto retrieve(Json& j) -> T;

    template< typename T >
    requires std::is_same_v< T, bool >
    static auto retrieve(Json& j) -> T;

    template< typename T >
    requires std::is_base_of_v< std::string, T >
    static auto retrieve(Json& j) -> T;

public:
    JSON_BASE(Json& json);
    JSON_BASE() = default;
};

#define JSON(type, name) \
type name{ [&](){\
    if(this->json)\
        return retrieve< type >(this->json.value().get().as< json::Object>()[#name]); \
    return type{}; \
    }()};

#define JSON_VEC(vType, name)                                                                  \
    std::vector< vType > name{[&](){                                                           \
        std::vector< vType > _temp{};                                                          \
        if(this->json)                                                                         \
        for(auto& it: this->json.value().get().as< json::Object>()[#name].as< json::Array >()) \
            _temp.push_back(JSON_BASE::retrieve< vType >(it));                                 \
        return _temp;                                                                          \
    }()};

#define JSON_OPT(vType, name)                                                                                       \
    std::optional< vType > name{[&](){                                                                              \
        if(this->json)                                                                                              \
        if(this->json.value().get().as< json::Object>().contains(#name))                                            \
            return std::optional< vType >{retrieve< vType >(this->json.value().get().as< json::Object >()[#name])}; \
        return std::optional< vType >{};                                                                            \
    }()};

}//namespace json