# Não sei qse nd de cmake, mas as dependencias aqui são bem simples então acho que tá tudo certo
# TODO testar no linux

cmake_minimum_required(VERSION 3.14)
project(MetodosNum2)

set(CMAKE_CXX_STANDARD 17)

# Procurar SDL2 e OpenGL no sistema (Tem que instalar o SDL2 em um caminho conhecido, instalar pelo gerenciador de pacotes deve funcionar)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Adicionar os .h's
include_directories(deps/include ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

# Compilar o código fonte do imgui
file(GLOB_RECURSE IMGUI_SRC "deps/imgui/*.cpp")
file(GLOB_RECURSE IMGUI_BACKENDS_SRC "deps/imgui/backends/*.cpp")
# Adicionar o código fonte compilado do imgui em uma biblioteca
add_library(imgui ${IMGUI_SRC} ${IMGUI_BACKENDS_SRC})

# Linkar as bibliotecas no programa
link_libraries(imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

# Compilar o código fonte em src
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Criar o executável a partir do código fonte :)
add_executable(MetodosNum2 ${SRC_FILES})