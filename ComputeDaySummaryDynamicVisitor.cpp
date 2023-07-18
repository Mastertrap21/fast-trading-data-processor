#include "ComputeDaySummaryDynamicVisitor.h"

// The visit method for DynamicStockT calls the base function
void ComputeDaySummaryDynamicVisitor::visit(DynamicStockT &item) noexcept {
    DynamicComputeDaySummaryVisitorT::visit(item);
}

// The visit method for DynamicDayHistoryT calls the base function
void ComputeDaySummaryDynamicVisitor::visit(DynamicDayHistoryT &item) noexcept {
    DynamicComputeDaySummaryVisitorT::visit(item);
}

// The visit method for DynamicTradeTransactionT calls the base function
void ComputeDaySummaryDynamicVisitor::visit(DynamicTradeTransactionT &item) noexcept {
    DynamicComputeDaySummaryVisitorT::visit(item);
}