cmake_minimum_required(VERSION 3.14)
project(MultiPass)

find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)
include_directories(Reddit)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Insta)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mainWindow)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Reddit)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SerialCommunication)


set(CMAKE_PREFIX_PATH /home/irolup/Documents/Qt/6.6.1/gcc_64/lib/cmake)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)


set(CMAKE_CXX_STANDARD 17)

add_executable(MultiPass main.cpp
        Insta/Insta.cpp
        mainWindow/mainWindow.cpp
        Reddit/redditDialog.cpp
        Reddit/redditDialog.h
        Controller.cpp
        Controller.h
        SerialCommunication/SerialCommunication.cpp
        SerialCommunication/SerialCommunication.h
        Autre/Autre.cpp
        Autre/Autre.h
        SerialCommunication/SerialCommunicationDialog.cpp
        SerialCommunication/SerialCommunicationDialog.h
        SerialCommunication/TransparentCircleWidget.cpp
        SerialCommunication/TransparentCircleWidget.h
        SerialCommunication/SerialCommunicationControler.cpp
        SerialCommunication/SerialCommunicationControler.h
        SerialCommunication/ConnectionSettingsDialog.cpp
        SerialCommunication/ConnectionSettingsDialog.h
        Reddit/RedditDownloader.cpp
        Reddit/RedditDownloader.h
)
target_link_libraries(MultiPass PRIVATE Qt6::Core Qt6::Widgets ${OPENGL_LIBRARIES})
target_link_libraries(MultiPass PRIVATE Qt6::SerialPort)
target_link_libraries(MultiPass PRIVATE CURL::libcurl)