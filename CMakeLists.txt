cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0079 NEW)

set(CMAKE_CXX_STANDARD 20)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/VERSION)
  file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION SPORE_VERSION)
else ()
  set(SPORE_VERSION 1.0.0)
endif ()

project(spore-embed VERSION ${SPORE_VERSION})

set(
  CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH}
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/spore/embed/embed_version.hpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/spore/embed/embed_version.hpp
)

add_compile_options(
  "$<$<CXX_COMPILER_ID:MSVC>:/bigobj>"
)

add_compile_definitions(
  SPDLOG_NO_SOURCE_LOC
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(
    SPDLOG_ACTIVE_LEVEL=0
  )
  add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/Od>"
    "$<$<CXX_COMPILER_ID:GNU>:-g3>"
    "$<$<CXX_COMPILER_ID:GNU>:-O0>"
    "$<$<CXX_COMPILER_ID:Clang>:-g>"
    "$<$<CXX_COMPILER_ID:Clang>:-O0>"
  )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_definitions(
    SPDLOG_ACTIVE_LEVEL=1
  )
  add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/O2;/DNDEBUG;/Zi;/Gy>"
    "$<$<CXX_COMPILER_ID:GNU>:-O3>"
    "$<$<CXX_COMPILER_ID:Clang>:-O3>"
  )
  add_link_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/DEBUG;/INCREMENTAL:NO;/OPT:REF;/OPT:ICF>"
  )
endif ()

add_subdirectory(src)