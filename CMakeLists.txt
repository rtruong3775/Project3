cmake_minimum_required(VERSION 3.16.3)
project(ProgrammingQuiz4)

set(CMAKE_CXX_STANDARD 14)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/bridges/lib)

include_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/include)
link_directories({CMAKE_CURRENT_SOURCE_DIR}/../libraries/curl/lib)

add_executable(ProgrammingQuiz4 ImdbTree.cpp)
target_link_libraries(ProgrammingQuiz4 libcurl.lib)
