cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake required

# Set the project name and version
project(ABC-implementation VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(ABC-implementation
    src/main.cpp     
    src/Bee.cpp
    src/EmployedBee.cpp
    src/FoodSource.cpp
    src/OnlookerBee.cpp
    src/Hive.cpp
    include/Bee.h
    include/EmployedBee.h
    include/OnlookerBee.h
    include/FoodSource.h
    include/Hive.h
    include/Shapes.h
)

# Include directories
target_include_directories(ABC-implementation PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Optionally, you can add link libraries if your project depends on external libraries
# For example:
# target_link_libraries(ABC-implementation PRIVATE some_library)
