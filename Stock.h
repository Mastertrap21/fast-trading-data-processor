#ifndef FTDP_STOCK_H
#define FTDP_STOCK_H

#include <string>
#include <memory>
#include <map>
#include "DayHistory.h"
#include "TradeTraits.h"

template <class Name, class DayHistoryContainer>
class Stock {
    static_assert(is_valid_dayHistoryContainer<DayHistoryContainer>::value, "DayHistoryContainer type is not valid"); // Make sure at compile time that DayHistoryContainer type is valid
    public:
    Name name; // name of the stock
    DayHistoryContainer dayHistories; // a container of the day histories for each day for this stock
    Stock(const Stock& that) = delete;  // remove the copy constructor, we don't want to copy information as the dataset is very large
    Stock& operator=(const Stock&) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    Stock(Name name) : name(name) { }; // initialization list / universal constructor
};

template <class Name, class DayHistoryContainer>
class DynamicStock : public Stock<Name, DayHistoryContainer>, public Item<DynamicVisitor> {
    static_assert(is_valid_dayHistoryContainer<DayHistoryContainer>::value, "DayHistoryContainer type is not valid"); // Make sure at compile time that DayHistoryContainer type is valid
public:
    DynamicStock(const DynamicStock& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicStock& operator=(const DynamicStock&) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicStock(Name name) : Stock<Name, DayHistoryContainer>(name) { }; // initialization list / universal constructor
    // Accept method implementation because this is the dynamic stock structures which will be used by the Dynamic visitors
    void accept(Visitor &visitor) noexcept override {
        acceptVisitor(*this, visitor);
    };
};

// Type definition for Stock using string for name, map of unique pointers of dayHistory for container
typedef Stock<std::string, std::map<int, std::unique_ptr<DayHistoryT>>> StockT;
// Type definition for Stock using string for name, map of unique pointers of dynamic dayHistory for container
typedef DynamicStock<std::string, std::map<int, std::unique_ptr<DynamicDayHistoryT>>> DynamicStockT;

// Specialization of the visitor trait with an accept method for any visitor
template<>
struct visitor_traits<StockT> {
    template<class VisitorType>
    static void accept(VisitorType &visitor, StockT &item) noexcept {
        visitor.visit(item); // visit the item using the visit method in the visitor
    }
};

#endif //FTDP_STOCK_H
