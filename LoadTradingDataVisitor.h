#ifndef FTDPT_LOADTRADINGDATAVISITOR_H
#define FTDP_LOADTRADINGDATAVISITOR_H

#include <string>
#include <memory>
#include <map>

#include "TradeTraits.h"

template <class Stock, class DayHistory, class TradeTransaction, class TradeTransactionInfo>
class LoadTradingDataVisitor {
    static_assert(is_valid_stock<Stock>::value, "Stock type is not valid"); // Make sure at compile time that Stock is valid
    static_assert(is_valid_dayHistory<DayHistory>::value, "DayHistory type is not valid"); // Make sure at compile time that DayHistory is valid
    static_assert(is_valid_tradeTransaction<TradeTransaction>::value, "TradeTransaction type is not valid"); // Make sure at compile time that TradeTransaction is valid
    static_assert(is_valid_tradeTransactionInfo<TradeTransactionInfo>::value, "TradeTransactionInfo type is not valid"); // Make sure at compile time that TradeTransactionInfo is valid
public:
    // A pointer because the visitor only uses it to load the information for the stocks inside the map
    // The ownership of the Stocks is handled by the map, therefore it is a map of unique pointers
    std::map<std::string, std::unique_ptr<Stock>> *stocksPtr;
    // Initializer list constructor that takes a pointer of map of unique pointers of Stock
    LoadTradingDataVisitor(std::map<std::string, std::unique_ptr<Stock>>* stocksPtr) : stocksPtr(stocksPtr) { }
    // Visit function for generic TradeTransactionInfo
    void visit(TradeTransactionInfo &tradeTransactionInfo) noexcept {
        auto& stock = (*stocksPtr)[tradeTransactionInfo.stock]; // Try to get a reference of the stock from the map pointer using the name
        if(stock == NULL){ // The stock was not found in the map, we need to create it
            stock = std::make_unique<Stock>(std::string(tradeTransactionInfo.stock)); // create the stock using make_unique in order to get a unique pointer for it
            // this is because the map is going to have the ownership of the stock, such that when the map is removed the stocks will also be removed
            (*stocksPtr)[stock.get()->name] = std::move(stock); // We are using move semantics to move the unique pointer inside the map, this is because we need to move it not copy it
            // It would also be impossible to copy it because it is unique smart pointer
        }

        // calculate the day number and cast it to integer, day numbers should be expressable in integers
        auto dayNumber = static_cast<int>(tradeTransactionInfo.timestamp/(60*60*24*1000));
        auto& dayHistory = stock.get()->dayHistories[dayNumber]; // Try to get a reference of the day history from the map pointer using the day number
        if(dayHistory == NULL){  // The stock was not found in the map, we need to create it
            dayHistory = std::make_unique<DayHistory>(dayNumber); // create the day history using make_unique in order to get a unique pointer for it
            stock.get()->dayHistories[dayNumber] = std::move(dayHistory);// We are using move semantics to move the unique pointer inside the map, this is because we need to move it not copy it
        }
        // create the trade transaction using make_unique in order to get a unique pointer for it
        auto tradeTransaction = std::make_unique<TradeTransaction>(static_cast<long>(tradeTransactionInfo.timestamp), static_cast<long>(tradeTransactionInfo.amount), static_cast<double>(tradeTransactionInfo.price));
        dayHistory.get()->tradeTransactions.push_back(std::move(tradeTransaction));// We are using move semantics to move the unique pointer inside the map, this is because we need to move it not copy it
    }
};

// DynamicLoadTradingDataVisitor type definition using dynamic structures type definitions
typedef LoadTradingDataVisitor<DynamicStockT, DynamicDayHistoryT, DynamicTradeTransactionT, DynamicTradeTransactionInfoT> DynamicLoadTradingDataVisitorT;
// StaticLoadTradingDataVisitor type definition using normal structures type definitions
typedef LoadTradingDataVisitor<StockT, DayHistoryT, TradeTransactionT, const TradeTransactionInfoT> StaticLoadTradingDataVisitorT;


#endif //FTDP_LOADTRADINGDATAVISITOR_H
