cmake_minimum_required(VERSION 2.8.11)

project(opengl-101)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES
	src/main.cpp
        src/MyGlWindow.h
        src/MyGlWindow.cpp
)

set(INCLUDE_DIRS src)

##########################################
# Dependencies

#Qt5
find_package(Qt5Widgets)
list(APPEND LIBRARIES Qt5::Widgets)

find_package(Qt5OpenGL)
list(APPEND LIBRARIES Qt5::OpenGL)

#Glew
find_package(GLEW REQUIRED)
list(APPEND INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
list(APPEND LIBRARIES ${GLEW_LIBRARIES})

#OpenGL
find_package(OpenGL REQUIRED)
list(APPEND LIBRARIES ${OPENGL_LIBRARIES})

##########################################
# Final setup
include_directories(${INCLUDE_DIRS})

add_executable(opengl-101 ${SOURCE_FILES})
target_link_libraries(opengl-101 ${LIBRARIES})