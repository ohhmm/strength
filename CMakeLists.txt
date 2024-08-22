cmake_minimum_required(VERSION 3.8)

# Select C++ active standard
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Git
find_package(Git QUIET)
if(NOT GIT_EXECUTABLE)
    find_program(GIT_EXECUTABLE git PATHS
        "$ENV{ProgramFiles}/Microsoft Visual Studio/*/*/Common7/IDE/CommonExtensions/Microsoft/TeamFoundation/Team Explorer/Git/cmd/"
    )
    find_package(Git)
endif()

# Fetch OpenMind
include(FetchContent)
FetchContent_Declare(openmind
    GIT_REPOSITORY https://github.com/ohhmm/openmind.git
    GIT_TAG main)
FetchContent_MakeAvailable(openmind)

# Add your project-specific configurations here

# Add CRC16 library
add_library(crc16 STATIC crc16.cpp)
target_include_directories(crc16 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(crc16 PRIVATE openmind)

if(BUILD_TESTS OR OPENMIND_BUILD_TESTS)
    enable_testing()
endif(BUILD_TESTS OR OPENMIND_BUILD_TESTS)

# Add your targets and link with OpenMind libraries as needed
# Example: target_link_libraries(your_target PRIVATE crc16 openmind)
