#pragma once

#include <format>
#include <stdexcept>

namespace spore::embed
{
    enum class embed_error_code
    {
        none,
        unknown,
        invalid,
        io,
    };

    struct embed_error final : std::runtime_error
    {
        embed_error_code error_code;

        template <typename... args_t>
        constexpr embed_error(const embed_error_code error_code, const std::format_string<args_t...> format, args_t&&... args)
            : std::runtime_error(std::format(format, std::forward<args_t>(args)...)),
              error_code(error_code)
        {
        }
    };
}
