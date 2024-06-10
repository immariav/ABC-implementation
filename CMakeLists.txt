cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake required

# Set the project name and version
project(ABC-implementation VERSION 1.0)

# Найдите Python 3.9
find_package(PythonInterp 3.9 REQUIRED)
find_package(PythonLibs 3.9 REQUIRED)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(/usr/local/include/python3.9)

# Add the executable
add_executable(ABC-implementation
    src/main.cpp     
    src/Bee.cpp
    src/EmployedBee.cpp
    src/FoodSource.cpp
    src/OnlookerBee.cpp
)

# Find Python
find_package(Python3 COMPONENTS Development REQUIRED)

# Include Python headers
target_include_directories(ABC-implementation PRIVATE ${Python3_INCLUDE_DIRS})

# Link against Python library
target_link_libraries(ABC-implementation PRIVATE ${Python3_LIBRARIES})