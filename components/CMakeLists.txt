add_library(components button.c)
target_compile_options(components PRIVATE -Wall -Wextra -g)

find_package(raylib 3.0 REQUIRED)
target_include_directories(components PRIVATE ${CMAKE_SOURCE_DIR}/utils)
target_link_libraries(components PRIVATE raylib utils)
