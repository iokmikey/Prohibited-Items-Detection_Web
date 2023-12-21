cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(jsonParse LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# qt5
find_package(Qt5 COMPONENTS 
    Core 
    Network 
    REQUIRED) # Qt COMPONENTS


include_directories(${CMAKE_SOURCE_DIR})


add_executable(${PROJECT_NAME}
    main.cpp
    JsonHelper.cpp
) 

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt5::Core 
)