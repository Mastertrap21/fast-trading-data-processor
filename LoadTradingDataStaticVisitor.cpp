#include "LoadTradingDataStaticVisitor.h"

// The visit method for TradeTransactionInfoT calls the base function
void LoadTradingDataStaticVisitor::visit(const TradeTransactionInfoT &item) noexcept {
    StaticLoadTradingDataVisitorT::visit(item);
}
