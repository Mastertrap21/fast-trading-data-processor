#ifndef FTDP_SAVEDAYSUMMARYVISITOR_H
#define FTDP_SAVEDAYSUMMARYVISITOR_H

#include <string>
#include <memory>
#include <map>
#include <limits>
#include <fstream>

#include "Stock.h"


template <class Stock, class DayHistory, class DaySummary>
class SaveDaySummaryVisitor {
    static_assert(is_valid_stock<Stock>::value, "Stock type is not valid"); // make sure at compile time that Stock template is valid using custom traits defined with help of SFINAE
    static_assert(is_valid_dayHistory<DayHistory>::value, "DayHistory type is not valid"); // make sure at compile time that DayHistory template is valid using custom traits defined with help of SFINAE
    static_assert(is_valid_daySummary<DaySummary>::value, "DaySummary type is not valid"); // make sure at compile time that DaySummary template is valid using custom traits defined with help of SFINAE
public:
    const Stock *currentStock{nullptr}; // current stock pointer used to know the name of the stock for the filename save
    std::ofstream outputFile; // file stream for output

    // For saving the daySummaries the Stock is just a container for DayHistories
    // So the visit method has to visit its dayHistories
    void visit(Stock &item) noexcept {
        currentStock = &item;
        for(auto &dayHistoryPair : item.dayHistories){
            auto dayHistory = dayHistoryPair.second.get();
            this->visit(*dayHistory);
        }
    }

    // For saving the daySummaries the DayHistory is just a container for the daySummary
    // So the visit method has to visit its daySummary
    void visit(DayHistory &item) noexcept {
        this->visit(item.daySummary);
    }

    // As this visitor saves the day summaries this visit method is the one that contains the business code
    // We make use of the stored current stock pointer to know in which stock we are
    void visit(DaySummary &item) noexcept {
        outputFile.open("output\\" + currentStock->name + "_" + std::to_string(item.dayNumber) + ".txt"); // open/create the file for this stock and this day
        // the info is output as clear text, could have also been binary or any other format, but for readability of the testing process it is like this for now
        outputFile<<item.openingPrice<<std::endl<<item.lowestPrice<<std::endl<<item.highestPrice<<std::endl<<item.closingPrice<<std::endl; // output the info
        outputFile.close(); // close the file stream
    }
};

// DynamicSaveDaySummaryVisitor type definition using dynamic structures type definitions
typedef SaveDaySummaryVisitor<DynamicStockT, DynamicDayHistoryT, DynamicDaySummaryT> DynamicSaveDaySummaryVisitorT;
// StaticSaveDaySummaryVisitor type definition using normal structures type definitions
typedef SaveDaySummaryVisitor<const StockT, const DayHistoryT, const DaySummaryT> StaticSaveDaySummaryVisitorT;


#endif //FTDP_SAVEDAYSUMMARYVISITOR_H
