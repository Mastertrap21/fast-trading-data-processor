#ifndef FTDP_DAYHISTORY_H
#define FTDP_DAYHISTORY_H

#include <memory>
#include <vector>
#include "DaySummary.h"
#include "TradeTransaction.h"

#include "TradeTraits.h"

template <class DayNumber, class DaySummary, class TradeTransactionContainer>
class DayHistory {
    static_assert(std::is_arithmetic<DayNumber>::value, "DayNumber type is not valid"); // Make sure at compile time that DayNumber type is valid
    static_assert(is_valid_daySummary<DaySummary>::value, "DaySummary type is not valid"); // Make sure at compile time that DaySummary type is valid
    static_assert(is_valid_tradeTransactionContainer<TradeTransactionContainer>::value, "TradeTransactionContainer type is not valid"); // Make sure at compile time that TradeTransactionContainer type is valid
public:
    DayNumber dayNumber; // the day number of this history
    DaySummary daySummary; // the summary object for this day
    TradeTransactionContainer tradeTransactions; // a container with the trade transactions that happened on this day
    DayHistory(const DayHistory& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DayHistory& operator=(const DayHistory&) = delete; // remove the copy assignment, we don't want to copy information as the dataset is very large
    DayHistory(DayNumber dayNumber)  : dayNumber(dayNumber), daySummary(dayNumber) { }; // initialization list / universal constructor
};

template <class DayNumber, class DaySummary, class TradeTransactionContainer>
class DynamicDayHistory : public DayHistory<DayNumber, DaySummary, TradeTransactionContainer>, public Item<DynamicVisitor> {
    static_assert(std::is_arithmetic<DayNumber>::value, "DayNumber type is not valid"); // Make sure at compile time that DayNumber type is valid
    static_assert(is_valid_daySummary<DaySummary>::value, "DaySummary type is not valid"); // Make sure at compile time that DaySummary type is valid
    static_assert(is_valid_tradeTransactionContainer<TradeTransactionContainer>::value, "TradeTransactionContainer type is not valid"); // Make sure at compile time that TradeTransactionContainer type is valid
public:
    DynamicDayHistory(const DynamicDayHistory& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicDayHistory& operator=(const DynamicDayHistory&) = delete; // remove the copy assignment, we don't want to copy information as the dataset is very large
    DynamicDayHistory(DayNumber dayNumber) :
            DayHistory<DayNumber, DaySummary, TradeTransactionContainer>::DayHistory(dayNumber) { }; // initialization list / universal constructor
    // Accept method implementation because this is the dynamic dayHistory structures which will be used by the Dynamic visitors
    void accept(Visitor &visitor) noexcept override {
        acceptVisitor(*this, visitor); // pass a reference to this object to the visitor object using visit method
    };
};

// Type definition for Day history using integer for day number, a type defined day Summary and vector of unique_ptr of a type defined trade transaction
typedef DayHistory<int, DaySummaryT, std::vector<std::unique_ptr<TradeTransactionT>>> DayHistoryT;
// Type definition for Day history using integer for day number, a type defined day Dynamic Summary and vector of unique_ptr of a type defined  dynamic trade transaction
typedef DynamicDayHistory<int, DynamicDaySummaryT, std::vector<std::unique_ptr<DynamicTradeTransactionT>>> DynamicDayHistoryT;

// Specialization of the visitor trait with an accept method for any visitor
template<>
struct visitor_traits<DayHistoryT> {
    template <class VisitorType>
    static void accept(VisitorType &visitor, DayHistoryT &item) noexcept {
        visitor.visit(item); // visit the item using the visit method in the visitor
    }
};


#endif //FTDP_DAYHISTORY_H
