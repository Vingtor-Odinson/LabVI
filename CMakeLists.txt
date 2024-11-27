cmake_minimum_required(VERSION 3.22.1)

project(ProjetoLabVI)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the directory containing the serial library header files
#include_directories("/tmp/usr/local/include/" "${CMAKE_SOURCE_DIR}/src/")
#link_directories("/tmp/usr/local/lib")

include_directories("${CMAKE_SOURCE_DIR}/src/serial/usr/local/include/" "${CMAKE_SOURCE_DIR}/src/")
link_directories("${CMAKE_SOURCE_DIR}/src/serial/usr/local/lib")


# Collect all source files from the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the serial library
target_link_libraries(${PROJECT_NAME} serial)

# Link OpenSSL, Crypto++, and MySQL/MariaDB libraries to the executable
# target_link_libraries(${PROJECT_NAME} ${MYSQL_LIBRARY})
