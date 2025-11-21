cmake_minimum_required(VERSION 3.10)
project(LC_Top_Interview_150_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/libs)


# Find all main.cpp files inside problems and all subdirectories
file(GLOB_RECURSE PROBLEM_MAINS "problems/**/main.cpp")

foreach(MAIN_FILE ${PROBLEM_MAINS})
    # Get the folder (directory) containing this main.cpp
    get_filename_component(DIR ${MAIN_FILE} DIRECTORY)

    # Extract the folder name to use as the executable name
    get_filename_component(NAME ${DIR} NAME)

    # Add executable using main.cpp + solution.cpp
    add_executable(${NAME}
        ${MAIN_FILE}
        ${DIR}/solution.cpp
    )

    target_include_directories(${NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/libs
    )
endforeach()


