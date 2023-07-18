#include "LoadTradingDataDynamicVisitor.h"

// The visit method for DynamicTradeTransactionInfoT calls the base function
void LoadTradingDataDynamicVisitor::visit(DynamicTradeTransactionInfoT &item) noexcept {
    DynamicLoadTradingDataVisitorT::visit(item);
}
