#ifndef FTDP_LOADTRADINGDATASTATICVISITOR_H
#define FTDP_LOADTRADINGDATASTATICVISITOR_H

#include <string>
#include "Library.h"
#include "ReadableTradeStructures.h"
#include "Stock.h"
#include "LoadTradingDataVisitor.h"

// The static visitor that loads the trading data needs to implement StaticLoadTradingDataVisitor in order to have access to the general visit function
class LoadTradingDataStaticVisitor : public StaticLoadTradingDataVisitorT, public StaticVisitor {
public:
    // Initializer list constructor that takes a pointer of map of unique pointers of Stock
    // It is passed as a pointer because the visitor only uses it to load the information for the stocks inside the map
    // The ownership of the Stocks is handled by the map, therefore it is a map of unique pointers
    LoadTradingDataStaticVisitor(std::map<std::string, std::unique_ptr<StockT>>* stocksPtr) : StaticLoadTradingDataVisitorT(stocksPtr) { }
    // Visit function declaration for TradeTransactionInfoT
    void visit(const TradeTransactionInfoT &item) noexcept;
};

#endif //FTDP_LOADTRADINGDATASTATICVISITOR_H
