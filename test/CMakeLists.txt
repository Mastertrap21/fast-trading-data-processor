set(PROJECT_UNITTEST_NAME "fast-trading-data-processor-tests")

project(${PROJECT_UNITTEST_NAME} LANGUAGES CXX)

set(SOURCE_FILES_TEST ../Library.h ../TradeTransaction.h ../ReadableTradeStructures.h ../LoadTradingDataDynamicVisitor.cpp ../LoadTradingDataDynamicVisitor.h ../Stock.h ../DayHistory.h ../DaySummary.h ../LoadTradingDataStaticVisitor.cpp ../LoadTradingDataStaticVisitor.h ../LoadTradingDataVisitor.h ../ComputeDaySummaryVisitor.h ../ComputeDaySummaryDynamicVisitor.cpp ../ComputeDaySummaryDynamicVisitor.h ../ComputeDaySummaryStaticVisitor.cpp ../ComputeDaySummaryStaticVisitor.h ../SaveDaySummaryVisitor.h ../SaveDaySummaryDynamicVisitor.cpp ../SaveDaySummaryDynamicVisitor.h ../SaveDaySummaryStaticVisitor.cpp ../SaveDaySummaryStaticVisitor.h ../TradeTraits.h)
add_executable(${PROJECT_UNITTEST_NAME} ${INCLUDE_PATH}
  ${SOURCE_FILES_TEST}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp)
  
target_link_libraries(${PROJECT_UNITTEST_NAME} PRIVATE ${CONAN_LIBS})
gtest_discover_tests(${PROJECT_UNITTEST_NAME})