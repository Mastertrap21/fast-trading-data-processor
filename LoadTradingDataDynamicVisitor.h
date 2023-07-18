#ifndef FTDP_LOADTRADINGDATADYNAMICVISITOR_H
#define FTDP_LOADTRADINGDATADYNAMICVISITOR_H

#include "Library.h"
#include "Stock.h"
#include "ReadableTradeStructures.h"
#include "LoadTradingDataVisitor.h"

// The dynamic visitor that loads the trading data needs to implement DynamicLoadTradingDataVisitor in order to have access to the general visit function
// It also needs to implement DynamicVisitor for each of the types it supports such that the DynamicVisitor template visit function can provide visit functions for all the supported types
class LoadTradingDataDynamicVisitor : public DynamicLoadTradingDataVisitorT, public DynamicVisitor<DynamicTradeTransactionInfoT> {
public:
    // Initializer list constructor that takes a pointer of map of unique pointers of DynamicStock
    // It is passed as a pointer because the visitor only uses it to load the information for the stocks inside the map
    // The ownership of the Stocks is handled by the map, therefore it is a map of unique pointers
    LoadTradingDataDynamicVisitor(std::map<std::string, std::unique_ptr<DynamicStockT>>* stocksPtr) : DynamicLoadTradingDataVisitorT(stocksPtr) { }
    // Visit function declaration for DynamicTradeTransactionInfoT
    void visit(DynamicTradeTransactionInfoT &item) noexcept override;
};


#endif //FTDP_LOADTRADINGDATADYNAMICVISITOR_H
