cmake_minimum_required(VERSION 3.24)

project(json_test VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(FIND_LIBRARY_USE_LIB64_PATHS True)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")


include(FetchContent)

FetchContent_Declare(htcw_json
    GIT_REPOSITORY https://github.com/codewitch-honey-crisis/htcw_json.git
    GIT_TAG 0.2.5
    GIT_SHALLOW ON
    FIND_PACKAGE_ARGS 0.2.5
)
FetchContent_MakeAvailable(htcw_json)

add_executable(json_test 
    main.cpp
)
target_link_libraries(json_test htcw_json htcw_io)

target_include_directories(json_test PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
  )
