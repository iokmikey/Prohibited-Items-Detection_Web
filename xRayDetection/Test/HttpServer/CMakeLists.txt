cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(httpServer LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_PREFIX_PATH "/home/wxxz/tools/Qt5.12.8/5.12.8/gcc_64") # Qt Kit Dir
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

# workspace
include_directories(${CMAKE_SOURCE_DIR})


link_directories(
    "/home/wxxz/workspace/DetectionOfContraband/Test/HttpServer/build"
)


add_executable(${PROJECT_NAME}
    main.cpp
) 

target_link_libraries(
    ${PROJECT_NAME}
    civetweb
    dl
    pthread
    )

