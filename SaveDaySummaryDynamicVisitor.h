#ifndef FTDP_SAVEDAYSUMMARYDYNAMICVISITOR_H
#define FTDP_SAVEDAYSUMMARYDYNAMICVISITOR_H

#include "Library.h"
#include "DaySummary.h"
#include "SaveDaySummaryVisitor.h"

// The dynamic visitor that saves the daySummaries needs to implement DynamicSaveDaySummaryVisitorT in order to have access to the general visit function
// It also needs to implement DynamicVisitor for each of the types it supports such that the DynamicVisitor template visit function can provide visit functions for all the supported types
class SaveDaySummaryDynamicVisitor : public DynamicSaveDaySummaryVisitorT, public DynamicVisitor<DynamicStockT>, public DynamicVisitor<DynamicDayHistoryT>, public DynamicVisitor<DynamicDaySummaryT> {
public:
    // Visit function declaration for DynamicStock
    void visit(DynamicStockT &item) noexcept override;
    // Visit function declaration for DynamicDayHistory
    void visit(DynamicDayHistoryT &item) noexcept override;
    // Visit function declaration for DynamicDaySummary
    void visit(DynamicDaySummaryT &item) noexcept override;
};

#endif //FTDP_SAVEDAYSUMMARYDYNAMICVISITOR_H
