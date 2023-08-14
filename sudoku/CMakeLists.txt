add_executable(sudoku main.c)
target_compile_options(sudoku PRIVATE -Wall -Wextra -g)

find_package(raylib 4.0 REQUIRED)
target_include_directories(sudoku PRIVATE ${CMAKE_SOURCE_DIR}/components)
target_link_libraries(sudoku PRIVATE raylib m components)
