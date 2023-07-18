#ifndef FTDP_SAVEDAYSUMMARYSTATICVISITOR_H
#define FTDP_SAVEDAYSUMMARYSTATICVISITOR_H


#include "Library.h"
#include "DaySummary.h"
#include "SaveDaySummaryVisitor.h"

// The static visitor that saves the daySummaries needs to implement StaticSaveDaySummaryVisitorT in order to have access to the general visit function
class SaveDaySummaryStaticVisitor : public StaticSaveDaySummaryVisitorT, public StaticVisitor {
public:
    // Visit function declaration for Stock, const because it does not get changed
    void visit(const StockT &item) noexcept;
    // Visit function declaration for DayHistory, const because it does not get changed
    void visit(const DayHistoryT &item) noexcept;
    // Visit function declaration for DaySummary, const because it does not get changed
    void visit(const DaySummaryT &item) noexcept;
};

#endif //FTDP_SAVEDAYSUMMARYSTATICVISITOR_H
