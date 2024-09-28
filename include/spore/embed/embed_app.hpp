#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include "fmt/format.h"

#include "spore/embed/embed_error.hpp"
#include "spore/embed/embed_options.hpp"
#include "spore/embed/utils/files.hpp"

namespace spore::embed
{
    struct embed_app
    {
        explicit embed_app(embed_options options)
            : _options(std::move(options))
        {
        }

        void run()
        {
            std::vector<std::uint8_t> bytes;
            if (!files::read_file(_options.file, bytes))
            {
                throw embed_error {embed_error_code::io, "cannot read input file, path={}", _options.file};
            }

            embed_bytes(bytes);
        }

      private:
        embed_options _options;

        void embed_bytes(const std::span<const std::uint8_t> bytes)
        {
            const auto embed_format = [&]<typename integer_t>(const std::span<const integer_t> ints) {
                switch (_options.format)
                {
                    case embed_format::hex: {
                        embed_hex(ints);
                        break;
                    }

                    case embed_format::none:
                    default: {
                        throw embed_error {embed_error_code::invalid, "invalid format"};
                    }
                }
            };

            switch (_options.bits)
            {
                case 8: {
                    embed_format(bytes);
                    break;
                }

                case 16: {
                    const auto* data = reinterpret_cast<const std::uint16_t*>(bytes.data());
                    const std::size_t count = bytes.size() / sizeof(std::uint16_t);
                    embed_format(std::span {data, count});
                    break;
                }

                case 32: {
                    const auto* data = reinterpret_cast<const std::uint32_t*>(bytes.data());
                    const std::size_t count = bytes.size() / sizeof(std::uint32_t);
                    embed_format(std::span {data, count});
                    break;
                }

                case 64: {
                    const auto* data = reinterpret_cast<const std::uint64_t*>(bytes.data());
                    const std::size_t count = bytes.size() / sizeof(std::uint64_t);
                    embed_format(std::span {data, count});
                    break;
                }

                default: {
                    throw embed_error {embed_error_code::invalid, "invalid bit count, value={}", _options.bits};
                }
            }
        }

        template <typename integer_t>
        void embed_hex(const std::span<const integer_t> integers)
        {
            constexpr std::string_view hex_prefix = "0x";
            constexpr std::string_view hex_suffix = ", ";
            constexpr std::size_t hex_count = 2;
            constexpr std::size_t hex_width = hex_prefix.size() + hex_suffix.size() + (hex_count * sizeof(integer_t));

            if (_options.width < hex_width)
            {
                throw embed_error {embed_error_code::invalid, "invalid width, value={} min={}", _options.width, hex_width};
            }

            const std::string format = fmt::format("{{:#0{}x}}, ", hex_count * sizeof(integer_t) + hex_count);

            std::size_t width = 0;

            for (const integer_t integer : integers)
            {
                if (width + hex_width > _options.width)
                {
                    width = 0;
                    _options.output << std::endl;
                }

                _options.output << fmt::vformat(format, fmt::make_format_args(integer));

                width += hex_width;
            }
        }
    };
}