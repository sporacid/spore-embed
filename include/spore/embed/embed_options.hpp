#pragma once

#include <cstddef>
#include <ostream>
#include <string>

#include "spore/embed/embed_format.hpp"

namespace spore::embed
{
    struct embed_options
    {
        std::ostream& output;
        std::string file;
        std::string indent;
        std::size_t bits = 0;
        std::size_t width = 0;
        embed_format format = embed_format::none;
        bool debug = false;
    };
}