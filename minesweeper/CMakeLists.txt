add_executable(minesweeper main.c game.c)
target_compile_options(minesweeper PRIVATE -Wall -Wextra -g)

find_package(raylib 3.0 REQUIRED)
target_include_directories(minesweeper PRIVATE ${CMAKE_SOURCE_DIR}/utils)
target_include_directories(minesweeper PRIVATE ${CMAKE_SOURCE_DIR}/components)
target_link_libraries(minesweeper PRIVATE raylib utils components)
