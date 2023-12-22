cmake_minimum_required(VERSION 3.27)
project(MultiPass)

find_package(OpenGL REQUIRED)
include_directories(Reddit)
include_directories(${OPENGL_INCLUDE_DIRS})

set(CMAKE_PREFIX_PATH "/home/irolup/Documents/Qt/6.6.1/gcc_64/lib/cmake")
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(MultiPass main.cpp
        Insta/Insta.cpp
        mainWindow/mainWindow.cpp
        Reddit/redditDialog.cpp
        Reddit/redditDialog.h)
target_link_libraries(MultiPass PRIVATE Qt6::Core Qt6::Widgets ${OPENGL_LIBRARIES})