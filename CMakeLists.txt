cmake_minimum_required(VERSION 3.16)
project(ProjetoPOO_RPG VERSION 1.0 LANGUAGES CXX)

# Requisito R3: Padrão C++17 estrito
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Biblioteca com as classes do domínio (R3)
add_library(rpg_lib
    src/Entidade.cpp
    src/Guerreiro.cpp
    src/Mago.cpp
    src/Grupo.cpp
)

# Permite #include "rpg/classe.hpp" (R2)
target_include_directories(rpg_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Portão de avisos obrigatório da Unidade I + -Werror (R3)
target_compile_options(rpg_lib PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wold-style-cast
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wnon-virtual-dtor
    -Wdouble-promotion
    -Wformat=2
    -Werror
)

# Executável principal ligado à biblioteca (R3)
add_executable(rpg_app src/main.cpp)
target_link_libraries(rpg_app PRIVATE rpg_lib)