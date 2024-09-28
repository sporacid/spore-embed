#pragma once

#include <string_view>

namespace spore::embed
{
    enum class embed_format
    {
        none,
        hex,
    };

    inline embed_format parse_format(const std::string_view value)
    {
        static const std::unordered_map<std::string_view, embed_format> value_map {
            {"none", embed_format::none},
            {"hex", embed_format::hex},
        };
        const auto it_value = value_map.find(value);
        return it_value != value_map.end() ? it_value->second : embed_format::none;
    }
}