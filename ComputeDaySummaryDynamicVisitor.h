#ifndef FTDP_COMPUTEDAYSUMMARYDYNAMICVISITOR_H
#define FTDP_COMPUTEDAYSUMMARYDYNAMICVISITOR_H

#include "Library.h"
#include "TradeTransaction.h"
#include "ComputeDaySummaryVisitor.h"

// The dynamic visitor that computes the daySummaries needs to implement DynamicComputeDaySummaryVisitor in order to have access to the general visit function
// It also needs to implement DynamicVisitor for each of the types it supports such that the DynamicVisitor template visit function can provide visit functions for all the supported types
class ComputeDaySummaryDynamicVisitor : public DynamicComputeDaySummaryVisitorT, public DynamicVisitor<DynamicStockT>, public DynamicVisitor<DynamicDayHistoryT>, public DynamicVisitor<DynamicTradeTransactionT> {
public:
    // Visit function declaration for DynamicStock
    void visit(DynamicStockT &item) noexcept override;
    // Visit function declaration for DynamicDayHistory
    void visit(DynamicDayHistoryT &item) noexcept override;
    // Visit function declaration for DynamicTradeTransaction
    void visit(DynamicTradeTransactionT &item) noexcept override;
};

#endif //FTDP_COMPUTEDAYSUMMARYDYNAMICVISITOR_H
