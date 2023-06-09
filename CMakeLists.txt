
#set(CMAKE_OSX_ARCHITECTURES=arm64)
#set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;arm64")
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(asteroid)

cmake_minimum_required(VERSION 3.9)

#set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")
#set(CMAKE_PREFIX_PATH "/Users/macbook/Qt/6.6.0/macos/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB MVC_SRCS mvc/view/*.cpp
        mvc/controller/*.cpp
        mvc/model/*.cpp)

add_executable(asteroid asteroid/main.cpp ${MVC_SRCS} asteroid/asteroid.qrc)
target_link_libraries(asteroid Qt::Core Qt::Widgets Qt::Multimedia)
target_include_directories(asteroid PRIVATE
        mvc/controller
        mvc/model
        mvc/view
        asteroid
        3rdparty/Streams/source)
