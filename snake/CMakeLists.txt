add_executable(snake main.c game.c snake.c)
target_compile_options(snake PRIVATE -Wall -Wextra -g)

find_package(raylib 3.0 REQUIRED)
target_include_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/utils)
target_link_libraries(snake PRIVATE raylib utils)
