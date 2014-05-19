project(opengl_qt5)
cmake_minimum_required(VERSION 2.8.12)

# Qt library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
set(CMAKE_AUTOMOC ON)

# OpenGL & GLEW library
find_package(OpenGL REQUIRED)

# executable
add_executable(opengl_qt5 main.cpp)
qt5_use_modules(opengl_qt5 Widgets OpenGL)
target_link_libraries(opengl_qt5 ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
