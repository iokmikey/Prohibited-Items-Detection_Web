cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/

project(xRayDetection LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)
enable_language(CXX)


# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# onnxruntime path
set(ONNXRUNTIME_HOME "")
if (NOT ONNXRUNTIME_HOME)
    set(ONNXRUNTIME_HOME "/home/ming/workspace/onnxruntime-linux-x64-1.15.1") # 默认我的onnxruntime路径
endif()
if(EXISTS ${ONNXRUNTIME_HOME})
    message("OnnxruntimeHome:${ONNXRUNTIME_HOME}")
else()
    message("The ${ONNXRUNTIME_HOME} onnxruntime_home dose not exist.")
    message(FATAL_ERROR "Please set the onnxruntime home var.")
endif()

include_directories(${ONNXRUNTIME_HOME}/include)
link_directories(${ONNXRUNTIME_HOME}/lib)


# current workspace
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_LIST "src/*.cpp" "src/*.c")	#遍历获取source/路径下所有的*.cpp和*.c文件列表
file(GLOB_RECURSE HDR_LIST "include/*.h" "include/*.hpp")

foreach(SRC ${SRC_LIST})
    message("src:" ${SRC})
endforeach()


add_executable(${PROJECT_NAME}
    ${SRC_LIST}
    ${HDR_LIST} 
) 

#add_dependencies(${PROJECT_NAME} INI)

# libcivetweb
set(CIVETWEB_PATH ${CMAKE_SOURCE_DIR}/external/civetweb)
set(LIBCIVETWEB "libcivetweb.a")
execute_process(
    COMMAND make -C ${CIVETWEB_PATH} clean lib WITH_CPP=1
)
execute_process(
    COMMAND cp ${CIVETWEB_PATH}/${LIBCIVETWEB} ${CMAKE_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    onnxruntime
    ${CMAKE_BINARY_DIR}/${LIBCIVETWEB} 
    ${OpenCV_LIBS}
    pthread
    dl
    )
