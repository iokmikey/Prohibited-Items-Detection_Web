cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(Commu LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/wxxz/tools/Qt5.12.8/5.12.8/gcc_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


# qt5
find_package(Qt5 COMPONENTS 
    Core 
    Network 
    REQUIRED) # Qt COMPONENTS


# workspace
include_directories(${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SRC_LIST "*.cpp")	#遍历获取source/路径下所有的*.cpp和*.c文件列表
file(GLOB_RECURSE HDR_LIST "*.h")


# add_executable(${PROJECT_NAME}
#     ${SRC_LIST}
#     ${HDR_LIST} 
# ) 

add_executable(
    server
    Server.cpp
    #SocketServer.h
    SocketServer.cpp
)

add_executable(
    client
    Client.cpp
)

target_link_libraries(server PRIVATE 
    Qt5::Core 
    Qt5::Network
    )

target_link_libraries(client PRIVATE 
    Qt5::Core 
    Qt5::Network
)