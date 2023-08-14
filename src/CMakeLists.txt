find_package(raylib 4.5 REQUIRED)

set(sources)
file(GLOB sources *.c)

foreach(source ${sources})
    get_filename_component(name ${source} NAME)
    string(REPLACE ".c" "" name ${name})

    add_executable(${name} ${source})
  target_compile_options(${name} PRIVATE -Wall -Wextra -ggdb -O2)
    target_link_libraries(${name} raylib)
endforeach()
