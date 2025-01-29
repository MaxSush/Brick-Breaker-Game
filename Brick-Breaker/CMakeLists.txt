# CMakeList.txt : CMake project for Far-Annoyed, include source and define
# project specific logic here.
#

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Brick-Breaker/external/imgui)

add_subdirectory("external/glfw")

include_directories("include" ${IMGUI_DIR} ${IMGUI_DIR}/backends)

add_subdirectory ("src")

# Add ImGui source files

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add ImGui sources to your target
target_sources(Game PRIVATE ${IMGUI_SOURCES})
