cmake_minimum_required(VERSION 3.9)

# Set the project name
project(asteroid)

# Ensure we are using at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Gather source files
file(GLOB MVC_SRCS mvc/view/*.cpp
        mvc/controller/*.cpp
        mvc/model/*.cpp)

# Create the executable
add_executable(asteroid main.cpp ${MVC_SRCS}
    mvc/model/ShieldFloater.h mvc/model/ShieldFloater.cpp
    mvc/model/WhiteCloudDebris.h mvc/model/Asteroid.h
    mvc/model/Bullet.h mvc/model/Falcon.h
    mvc/model/Floater.h mvc/model/Movable.h
    mvc/model/Nuke.h mvc/model/NukeFloater.h mvc/model/PolarPoint.h
    mvc/model/Sprite.h mvc/model/Star.h
    mvc/controller/CommandCenter.h mvc/controller/Game.h
    mvc/controller/GameOp.h mvc/controller/GameOpsQueue.h
    mvc/controller/Utils.h mvc/view/GameFrame.h mvc/view/GamePanel.h
    mvc/model/whiteclouddebris.cpp
    mvc/model/nuke.cpp
    mvc/model/Floater.cpp
    mvc/controller/assetsloader.h mvc/controller/assetsloader.cpp

)

# Link SFML libraries to the executable
target_link_libraries(asteroid sfml-graphics sfml-window sfml-system sfml-audio)

# Include directories
target_include_directories(asteroid PRIVATE
    mvc/controller
    mvc/model
    mvc/view
    asteroid
    ${SFML_INCLUDE_DIRS})
