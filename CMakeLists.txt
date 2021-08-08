cmake_minimum_required(VERSION 3.14)
project(MagicCube)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
include_directories(${GLFW_H} include)

set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib)
link_libraries(${OPENGL} ${GLFW_LINK})

aux_source_directory(src SRC_LIST)

add_executable(MagicCube ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if (APPLE)
    target_link_libraries(MagicCube "-framework OpenGL")
    target_link_libraries(MagicCube "-framework GLUT")
endif()