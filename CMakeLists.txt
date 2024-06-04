cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake required

# Set the project name and version
project(ABC-implementation VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(MAVLink REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(~/mavlink/install/include)
include_directories(/usr/include/mavsdk)

# Add the executable
add_executable(ABC-implementation
    src/main.cpp     
    src/Bee.cpp
    src/EmployedBee.cpp
    src/FoodSource.cpp
    src/OnlookerBee.cpp
    src/Hive.cpp
)