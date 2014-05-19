cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project(qglviewer_qt4)

#--- Edit this line to force the system to find the right Qt4
set(QT_QMAKE_EXECUTABLE "/usr/local/bin/qmake")

#--- Tell where to find custom cmake files (for find_package)
set(CMAKE_MODULE_PATH ../cmake)

#--- Qt4
find_package(Qt4 4.8.1 REQUIRED QtCore QtGui QtOpenGL QtXml)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
list(APPEND libs ${QT_LIBRARIES})

#--- OpenGL
find_package(OpenGL REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
list(APPEND libs ${OPENGL_LIBRARIES})

#--- QGLViewer
find_package(QGLViewer REQUIRED)
include_directories(${QGLVIEWER_INCLUDE_DIR})
list(APPEND libs ${QGLVIEWER_LIBRARIES})
# message(STATUS ${QGLVIEWER_LIBRARIES})

#--- Add all sources in this folder
file(GLOB_RECURSE hdrs "*.h")
file(GLOB_RECURSE srcs "*.cpp")

#--- Create executable and link
add_executable(qglviewer_qt4 ${hdrs} ${srcs})
target_link_libraries(qglviewer_qt4 ${libs})
