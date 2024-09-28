set(
  SPORE_EMBED_BINARY_TARGET ${PROJECT_NAME}-bin
  CACHE STRING "Target for the main embed application"
)

set(
  SPORE_EMBED_LIBRARY_TARGET ${PROJECT_NAME}-lib
  CACHE STRING "Target for the main embed library"
)

set(
  SPORE_EMBED_BINARY_NAME spore-embed
  CACHE STRING "Output name for the main embed application"
)

add_library(
  ${SPORE_EMBED_LIBRARY_TARGET}
  INTERFACE
)

find_package(spdlog CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

target_link_libraries(
  ${SPORE_EMBED_LIBRARY_TARGET}
  INTERFACE
    spdlog::spdlog
)

target_include_directories(
  ${SPORE_EMBED_LIBRARY_TARGET}
  INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

file(
  GLOB_RECURSE SPORE_EMBED_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/**.hpp
    ${PROJECT_SOURCE_DIR}/src/**.cpp
)

add_executable(
  ${SPORE_EMBED_BINARY_TARGET}
  ${SPORE_EMBED_SOURCE_FILES}
)

set_target_properties(
  ${SPORE_EMBED_BINARY_TARGET}
  PROPERTIES
    LINKER_LANGUAGE CXX
    OUTPUT_NAME ${SPORE_EMBED_BINARY_NAME}
)

target_link_libraries(
  ${SPORE_EMBED_BINARY_TARGET}
  PRIVATE
    ${SPORE_EMBED_LIBRARY_TARGET}
    argparse::argparse
)

include(GNUInstallDirs)

install(
  TARGETS ${SPORE_EMBED_BINARY_TARGET}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "**.hpp"
)

install(
  FILES ${PROJECT_SOURCE_DIR}/cmake/SporeEmbed.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
)