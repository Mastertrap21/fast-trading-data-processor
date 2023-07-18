#include "SaveDaySummaryStaticVisitor.h"

// The visit method for StockT calls the base function
void SaveDaySummaryStaticVisitor::visit(const StockT &item) noexcept {
    StaticSaveDaySummaryVisitorT::visit(item);
}

// The visit method for DayHistoryT calls the base function
void SaveDaySummaryStaticVisitor::visit(const DayHistoryT &item) noexcept {
    StaticSaveDaySummaryVisitorT::visit(item);
}

// The visit method for DaySummaryT calls the base function
void SaveDaySummaryStaticVisitor::visit(const DaySummaryT &item) noexcept {
    StaticSaveDaySummaryVisitorT::visit(item);
}