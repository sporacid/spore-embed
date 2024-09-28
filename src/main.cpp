#include <iostream>

#include "argparse/argparse.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "spore/embed/embed_app.hpp"
#include "spore/embed/embed_error.hpp"
#include "spore/embed/embed_options.hpp"
#include "spore/embed/embed_version.hpp"

namespace spore::embed::detail::metavars
{
    constexpr auto file = "FILE";
    constexpr auto format = "FORMAT";
    constexpr auto integer = "INTEGER";
}

int main(const int argc, const char* argv[])
{
    using namespace spore::embed;

    const auto sinks = {std::make_shared<spdlog::sinks::stderr_color_sink_st>()};
    const auto logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

    spdlog::set_default_logger(logger);
    spdlog::set_pattern("%l: %v");

    argparse::ArgumentParser arg_parser {
        SPORE_EMBED_NAME,
        SPORE_EMBED_VERSION,
    };

    arg_parser
        .add_argument("file")
        .help("The file to embed")
        .metavar(detail::metavars::file);

    arg_parser
        .add_argument("-w", "--width")
        .help("Number of characters per rows to output")
        .metavar(detail::metavars::integer)
        .default_value<std::size_t>(80)
        .scan<'i', std::size_t>();

    arg_parser
        .add_argument("-b", "--bits")
        .help("Number of bits of the output")
        .metavar(detail::metavars::integer)
        .choices(8, 16, 32, 64)
        .default_value<std::size_t>(8)
        .scan<'i', std::size_t>();

    arg_parser
        .add_argument("-f", "--format")
        .help("Format of the output")
        .metavar(detail::metavars::format)
        .default_value("hex")
        .choices("hex");

    arg_parser
        .add_argument("-d", "--debug")
        .help("Enable debug output")
        .default_value(false)
        .implicit_value(true);

    try
    {
        arg_parser.parse_args(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << arg_parser;
        return static_cast<int>(embed_error_code::invalid);
    }

    const auto format = arg_parser.get<std::string>("--format");
    embed_options options {
        .output = std::cout,
        .file = arg_parser.get<std::string>("file"),
        .bits = arg_parser.get<std::size_t>("--bits"),
        .width = arg_parser.get<std::size_t>("--width"),
        .format = parse_format(format),
        .debug = arg_parser.get<bool>("--debug"),
    };

    if (options.debug)
    {
        spdlog::set_level(spdlog::level::debug);
    }

    try
    {
        embed_app app {
            std::move(options),
        };

        app.run();
    }
    catch (const embed_error& e)
    {
        SPDLOG_ERROR(e.what());
        return static_cast<int>(e.error_code);
    }
    catch (const std::exception& e)
    {
        SPDLOG_ERROR("failed to run embed: {}", e.what());
        return static_cast<int>(embed_error_code::unknown);
    }
    catch (...)
    {
        SPDLOG_ERROR("failed to run embed");
        return static_cast<int>(embed_error_code::unknown);
    }

    return static_cast<int>(embed_error_code::none);
}