#include "SaveDaySummaryDynamicVisitor.h"

// The visit method for DynamicStockT calls the base function
void SaveDaySummaryDynamicVisitor::visit(DynamicStockT &item) noexcept {
    DynamicSaveDaySummaryVisitorT::visit(item);
}

// The visit method for DynamicDayHistoryT calls the base function
void SaveDaySummaryDynamicVisitor::visit(DynamicDayHistoryT &item) noexcept {
    DynamicSaveDaySummaryVisitorT::visit(item);
}

// The visit method for DynamicDaySummaryT calls the base function
void SaveDaySummaryDynamicVisitor::visit(DynamicDaySummaryT &item) noexcept {
    DynamicSaveDaySummaryVisitorT::visit(item);
}