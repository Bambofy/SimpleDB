cmake_minimum_required(VERSION 3.17)
project(SimpleDB)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE ALL_SRCS
        "${CMAKE_CURRENT_SOURCE_DIR}/SimpleDB++/*.c*"
        )
file(GLOB_RECURSE ALL_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/SimpleDB++/*.h*"
        )

find_package(SQLite3 REQUIRED)

#add_executable(SimpleDB main.cpp ${ALL_SRCS} ${ALL_HEADERS})
add_library(SimpleDB SHARED ${ALL_SRCS} ${ALL_HEADERS})
target_link_libraries(SimpleDB ${SQLite3_LIBRARIES})
target_include_directories(SimpleDB PRIVATE ${SQLite3_INCLUDE_DIRS})