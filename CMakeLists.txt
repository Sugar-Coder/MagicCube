cmake_minimum_required(VERSION 3.14)
project(MagicCube)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(INC_H /usr/local/include)

include_directories(${GLFW_H} ${GLEW_H} ${INC_H} include)

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

aux_source_directory(src SRC_LIST)

add_executable(MagicCube ${SRC_LIST})

add_executable(test test/test.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if (APPLE)
    target_link_libraries(MagicCube "-framework OpenGL")
    target_link_libraries(MagicCube "-framework GLUT")
endif()