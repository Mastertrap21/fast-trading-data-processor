#include "ComputeDaySummaryStaticVisitor.h"

// The visit method for StockT calls the base function
void ComputeDaySummaryStaticVisitor::visit(const StockT &item) noexcept {
    StaticComputeDaySummaryVisitorT::visit(item);
}

// The visit method for DayHistoryT calls the base function
void ComputeDaySummaryStaticVisitor::visit(DayHistoryT &item) noexcept {
    StaticComputeDaySummaryVisitorT::visit(item);
}

// The visit method for TradeTransactionT calls the base function
void ComputeDaySummaryStaticVisitor::visit(const TradeTransactionT &item) noexcept {
    StaticComputeDaySummaryVisitorT::visit(item);
}