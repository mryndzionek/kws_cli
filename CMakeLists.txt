cmake_minimum_required(VERSION 3.16.3)

project(kws_cli)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")

include_directories(include)
set(LIBS m)

add_compile_options(-Wno-deprecated-declarations
                    -Wall -Werror -fPIC)

add_executable(kws_cli src/kws_cli.c src/fbank.c)
target_link_libraries(kws_cli ${LIBS})


