#ifndef FTDP_COMPUTEDAYSUMMARYVISITOR_H
#define FTDP_COMPUTEDAYSUMMARYVISITOR_H

#undef min
#undef max


#include <string>
#include <memory>
#include <map>
#include <limits>

#include "Stock.h"
#include "TradeTraits.h"

template <class Stock, class DayHistory, class TradeTransaction>
class ComputeDaySummaryVisitor {
    static_assert(is_valid_stock<Stock>::value, "Stock type is not valid"); // make sure at compile time that Stock template is valid using custom traits defined with help of SFINAE
    static_assert(is_valid_dayHistory<DayHistory>::value, "DayHistory type is not valid"); // make sure at compile time that DayHistory template is valid using custom traits defined with help of SFINAE
    static_assert(is_valid_tradeTransaction<TradeTransaction>::value, "TradeTransaction type is not valid"); // make sure at compile time that TradeTransaction template is valid using custom traits defined with help of SFINAE
public:
    DayHistory *currentDayHistory{nullptr};
    long earliestTimestamp{std::numeric_limits<long>::max()}; // default to max
    long latestTimestamp{std::numeric_limits<long>::min()}; // default to min

    // For computing the daySummaries the Stock is just a container for DayHistories
    // So the visit method has to visit its dayHistories
    void visit(const Stock &item) noexcept {
        for(auto &dayHistoryPair : item.dayHistories){ // loop the day histories
            auto dayHistory = dayHistoryPair.second.get(); // get a pointer to the current day history
            this->visit(*dayHistory); // visit it
        }
    }

    // For computing the daySummaries the DayHistory is just a container for the tradeTransactions
    // So the visit method has to visit its tradeTransactions
    // It also contains the daySummary that we need to update while computing
    void visit(DayHistory &item) noexcept {
        currentDayHistory = &item; // we save a pointer to the current day history as it contains the daySummary that needs to be updated by the transaction visit method
        earliestTimestamp = std::numeric_limits<long>::max(); // a new day... reset earliest timestamp
        latestTimestamp = std::numeric_limits<long>::min(); // a new day... reset latestTimestamp timestamp
        for(auto &tradeTransactionPtr : item.tradeTransactions){ // loop the transactions
            this->visit(*tradeTransactionPtr); // visit it
        }
    }

    // As this visitor computes the day summaries this visit method is the one that contains the business code
    // We make use of the stored current day history pointer to know in which day we are
    // We make use of the timestamp we save to know when to update the opening and closing prices
    void visit(const TradeTransaction &item) noexcept {
        if(item.timestamp < earliestTimestamp){ // We have a new opening price
            earliestTimestamp = item.timestamp; // Update the timestamp
            currentDayHistory->daySummary.openingPrice = item.price;  // Update the price
        }
        if(item.timestamp > latestTimestamp){ // We have a new closing price
            latestTimestamp = item.timestamp; // Update the timestamp
            currentDayHistory->daySummary.closingPrice = item.price; // Update the price
        }
        if(item.price < currentDayHistory->daySummary.lowestPrice){ // We have a new lowestPrice price
            currentDayHistory->daySummary.lowestPrice = item.price; // Update the price
        }
        if(item.price > currentDayHistory->daySummary.highestPrice){ // We have a new highestPrice price
            currentDayHistory->daySummary.highestPrice = item.price; // Update the price
        }
    }
};

// DynamicComputeDaySummaryVisitor type definition using dynamic structures type definitions
typedef ComputeDaySummaryVisitor<DynamicStockT, DynamicDayHistoryT, DynamicTradeTransactionT> DynamicComputeDaySummaryVisitorT;
// StaticComputeDaySummaryVisitor type definition using normal structures type definitions
typedef ComputeDaySummaryVisitor<const StockT, DayHistoryT, const TradeTransactionT> StaticComputeDaySummaryVisitorT;


#endif //FTDP_COMPUTEDAYSUMMARYVISITOR_H
