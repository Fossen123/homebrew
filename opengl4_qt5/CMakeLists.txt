cmake_minimum_required(VERSION 2.8.12)
project(opengl4_qt5)

#--- where to find Qt?
set(QT_QMAKE_EXECUTABLE "/usr/local/bin/qmake")
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt5/5.3.0")

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
set(CMAKE_AUTOMOC ON)

# executable
add_executable(opengl4_qt5 main.cpp)
qt5_use_modules(opengl4_qt5 Widgets OpenGL)
target_link_libraries(opengl4_qt5 ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
