cmake_minimum_required(VERSION 3.6)
project(fast-trading-data-processor)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Library.h TradeTransaction.h ReadableTradeStructures.h LoadTradingDataDynamicVisitor.cpp LoadTradingDataDynamicVisitor.h Stock.h DayHistory.h DaySummary.h LoadTradingDataStaticVisitor.cpp LoadTradingDataStaticVisitor.h LoadTradingDataVisitor.h ComputeDaySummaryVisitor.h ComputeDaySummaryDynamicVisitor.cpp ComputeDaySummaryDynamicVisitor.h ComputeDaySummaryStaticVisitor.cpp ComputeDaySummaryStaticVisitor.h SaveDaySummaryVisitor.h SaveDaySummaryDynamicVisitor.cpp SaveDaySummaryDynamicVisitor.h SaveDaySummaryStaticVisitor.cpp SaveDaySummaryStaticVisitor.h TradeTraits.h)
add_executable(fast-trading-data-processor ${SOURCE_FILES})

enable_testing()
