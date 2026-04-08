cmake_minimum_required(VERSION 3.11)
project(Game)

include(FetchContent)

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

set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

FetchContent_MakeAvailable(glfw)

target_include_directories(glfw INTERFACE ${glfw_SOURCE_DIR}/include)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.8-docking
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

find_package(OpenGL REQUIRED)

add_executable(my_app 
    src/main.cpp
    src/Scenes/MenuScene.h
    src/Core/Scenes/Scene.h
    src/Core/Scenes/SceneManager.h
    src/ECS/Components/Position.h
    src/ECS/Systems/DebugSystem.h
)

target_include_directories(my_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/_deps/ecs-src
)

if(WIN32)
    target_link_libraries(my_app 
        PRIVATE 
            fmt::fmt
            glfw
            imgui
            OpenGL::GL
            gdi32
            user32
            shell32
            kernel32
    )
else()
    target_link_libraries(my_app 
        PRIVATE 
            fmt::fmt
            glfw
            imgui
            OpenGL::GL
    )
endif()