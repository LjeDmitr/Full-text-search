set(target_name binaryLib)
set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/binary/binaryTrie.hpp" "${CMAKE_SOURCE_DIR}/include/binary/dictionary.hpp"
                "${CMAKE_SOURCE_DIR}/include/binary/docs.hpp" "${CMAKE_SOURCE_DIR}/include/binary/entries.hpp"
                "${CMAKE_SOURCE_DIR}/include/binary/header.hpp" "${CMAKE_SOURCE_DIR}/include/binary/binary.hpp")

add_library(${target_name} STATIC
  binaryTrie.cpp
  dictionary.cpp
  docs.cpp
  entries.cpp
  header.cpp
  binary.cpp
  ${HEADER_LIST})

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
  ${target_name}
  PRIVATE
    index
)