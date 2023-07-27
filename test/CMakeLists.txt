set(PROJECT_UNITTEST_NAME   "fast-trading-data-processor-tests")

project(${PROJECT_UNITTEST_NAME} LANGUAGES CXX)

add_executable(${PROJECT_UNITTEST_NAME} ${INCLUDE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp)
  
target_link_libraries(${PROJECT_UNITTEST_NAME} PRIVATE ${CONAN_LIBS})
gtest_discover_tests(${PROJECT_UNITTEST_NAME})