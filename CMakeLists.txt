cmake_minimum_required(VERSION  3.20)
project(run CXX)

set(CMAKE_CXX_FLAGS -std=c++17)

find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/gnuplot-iostream")

file(GLOB SRCS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})