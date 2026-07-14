include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

# Unit tests — no database
add_executable(test_score test_score.cpp)
target_link_libraries(test_score PRIVATE score_lib Catch2::Catch2WithMain)

add_test(NAME unit_tests COMMAND test_score)

# Integration tests — requires database
if(pqxx_FOUND)
  add_executable(test_database test_database.cpp)
  target_link_libraries(test_database PRIVATE score_lib database_lib Catch2::Catch2WithMain)
  add_test(NAME integration_tests COMMAND test_database)
  set_tests_properties(integration_tests PROPERTIES LABELS "integration")
endif()
