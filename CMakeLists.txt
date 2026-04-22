cmake_minimum_required(VERSION 3.11)
project(Game)

include(FetchContent)
#Application
add_executable(my_app 
  src/main.cpp
  src/app/Core/Graphics/Vertex/EBO.cpp
  src/app/Core/Graphics/Vertex/VBO.cpp
  src/app/Core/Graphics/Vertex/VAO.cpp
  src/app/Core/Graphics/Shader/shader.cpp
  src/app/Core/Graphics/Texture/texture.cpp
  _deps_external/glad/src/glad.c
)
#Downloads
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  ecs
  GIT_REPOSITORY https://github.com/redxdev/ECS
  GIT_TAG 5f74e19
)
FetchContent_MakeAvailable(ecs)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.8-docking
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
  SOURCE_SUBDIR .
)
FetchContent_MakeAvailable(stb)
#Constants
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

set(STB_IMPL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/_deps_external/stb_image/src/stb_image_impl.c)
file(WRITE ${STB_IMPL_FILE} "#define STB_IMAGE_IMPLEMENTATION\n#include <stb_image.h>\n")
#IncludeLibrary
find_package(OpenGL REQUIRED)

add_library(stb_image STATIC ${STB_IMPL_FILE})
target_include_directories(stb_image PUBLIC ${stb_SOURCE_DIR})

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC 
  ${imgui_SOURCE_DIR} 
  ${imgui_SOURCE_DIR}/backends
)
target_include_directories(glfw INTERFACE 
  ${glfw_SOURCE_DIR}/include
)

target_include_directories(my_app PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/_deps/ecs-src
  ${CMAKE_CURRENT_SOURCE_DIR}/_deps_external/glad/include
  ${stb_SOURCE_DIR}
)
#LinkLibrary
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

target_link_libraries(my_app PRIVATE
  fmt::fmt
  glfw
  imgui
  OpenGL::GL
  glm::glm
  stb_image
)

if(WIN32)
  target_link_libraries(my_app PRIVATE gdi32 user32 shell32 kernel32)
endif()