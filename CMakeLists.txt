cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ABC-for-simulation)

# Стандарт C++
set(CMAKE_CXX_STANDARD 14)

# Добавление исходных файлов
set(SOURCE_FILES
    src/main.cpp
    src/Bee.cpp
    src/EmployedBee.cpp
    src/OnlookerBee.cpp
    src/FoodSource.cpp
    src/Hive.cpp
    include/Shapes.h
    include/Bee.h
    include/EmployedBee.h
    include/OnlookerBee.h
    include/FoodSource.h
    include/Hive.h
)

# Включение директорий для заголовочных файлов
include_directories(include)

# Создание исполняемого файла из исходных файлов
add_executable(ABC-for-simulation ${SOURCE_FILES})

# Подключение библиотек, если необходимо
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(ABC-for-simulation SomeLibrary::SomeLibrary)
