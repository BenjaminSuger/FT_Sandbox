cmake_minimum_required(VERSION 3.15)
project(ft_sandbox CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# Main library
add_library(score_lib src/Score.cpp)
target_include_directories(score_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Postgres client — avoid fetching if not needed (for quick unit tests)
find_package(pqxx QUIET)

if(pqxx_FOUND)
  add_library(database_lib src/Database.cpp)
  target_include_directories(database_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
  target_link_libraries(database_lib pqxx)
endif()

# Executable
if(pqxx_FOUND)
  add_executable(ft_sandbox src/main.cpp)
  target_link_libraries(ft_sandbox score_lib database_lib)
else()
  message(WARNING "libpqxx not found; main executable will not be built")
endif()

# Tests
enable_testing()
add_subdirectory(tests)
