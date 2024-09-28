#pragma once

#include <fstream>
#include <string_view>
#include <vector>

namespace spore::embed::files
{
    inline bool read_file(const std::string_view path, std::vector<std::uint8_t>& bytes)
    {
        std::ifstream stream(path.data(), std::ios::in | std::ios::binary);
        if (!stream.is_open())
        {
            return false;
        }

        bytes = {
            std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>(),
        };

        stream.close();
        return !stream.bad();
    }
}
