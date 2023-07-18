#ifndef FTDP_COMPUTEDAYSUMMARYSTATICVISITOR_H
#define FTDP_COMPUTEDAYSUMMARYSTATICVISITOR_H


#include "Library.h"
#include "TradeTransaction.h"
#include "ComputeDaySummaryVisitor.h"

// The static visitor that computes the daySummaries needs to implement StaticComputeDaySummaryVisitor in order to have access to the general visit function
class ComputeDaySummaryStaticVisitor : public StaticComputeDaySummaryVisitorT, public StaticVisitor {
public:
    // Visit function declaration for Stock
    // const because the stock itself does not get changed
    void visit(const StockT &item) noexcept;
    // Visit function declaration for DayHistory
    void visit(DayHistoryT &item) noexcept;
    // Visit function declaration for TradeTransaction
    // const because the TradeTransaction does not get changed
    void visit(const TradeTransactionT &item) noexcept;
};


#endif //FTDP_COMPUTEDAYSUMMARYSTATICVISITOR_H
