cmake_minimum_required(VERSION 3.24)
project(kernel_image_processing_sequential)

set(CMAKE_CXX_STANDARD 17)

add_executable(kernel_image_processing_sequential main.cpp KernelImageProcessing.cpp KernelImageProcessing.h CSV.h CSV.cpp)
target_link_libraries(kernel_image_processing_sequential png)

