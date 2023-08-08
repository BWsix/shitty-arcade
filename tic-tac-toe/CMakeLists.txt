add_executable(tic-tac-toe main.c ai.c)
target_compile_options(tic-tac-toe PRIVATE -Wall -Wextra -g)

find_package(raylib 3.0 REQUIRED)
target_include_directories(tic-tac-toe PRIVATE ${CMAKE_SOURCE_DIR}/components)
target_link_libraries(tic-tac-toe PRIVATE raylib components)
