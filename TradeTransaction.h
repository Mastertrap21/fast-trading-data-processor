#ifndef FTDP_TRADETRANSACTION_H
#define FTDP_TRADETRANSACTION_H

#include <memory>
#include "Library.h"

template <typename Timestamp, typename Amount, typename Price>
class TradeTransaction {
    static_assert(std::is_integral<Timestamp>::value, "Timestamp type is not valid"); // Make sure at compile time that Timestamp type is valid
    static_assert(std::is_arithmetic<Amount>::value, "Amount type is not valid"); // Make sure at compile time that Amount type is valid
    static_assert(std::is_floating_point<Price>::value, "Price type is not valid"); // Make sure at compile time that Price type is valid
public:
    Timestamp timestamp;
    Amount amount;
    Price price;
    TradeTransaction(const TradeTransaction& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    TradeTransaction& operator=(const TradeTransaction&) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    TradeTransaction(Timestamp timestamp, Amount amount, Price price) :
            timestamp(timestamp), amount(amount), price(price)  { } // initialization list / universal constructor
};

template <typename Timestamp, typename Amount, typename Price>
class DynamicTradeTransaction : public TradeTransaction<Timestamp, Amount, Price>, public Item<DynamicVisitor> {
    static_assert(std::is_integral<Timestamp>::value, "Timestamp type is not valid"); // Make sure at compile time that Timestamp type is valid
    static_assert(std::is_arithmetic<Amount>::value, "Amount type is not valid"); // Make sure at compile time that Amount type is valid
    static_assert(std::is_floating_point<Price>::value, "Price type is not valid"); // Make sure at compile time that Price type is valid
public:
    DynamicTradeTransaction(const DynamicTradeTransaction& that) = delete;  // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicTradeTransaction& operator=(const DynamicTradeTransaction&) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicTradeTransaction(Timestamp timestamp, Amount amount, Price price) :
            TradeTransaction<Timestamp, Amount, Price>::TradeTransaction(timestamp, amount, price) { } // initialization list / universal constructor
    // Accept method implementation because this is the dynamic trade transaction structures which will be used by the Dynamic visitors
    void accept(Visitor &visitor) noexcept override {
        acceptVisitor(*this, visitor);
    };
};

// Type definition for TradeTransaction using long for timestamp, long for amount and double for price
typedef TradeTransaction<long, long, double> TradeTransactionT;
// Type definition for dynamic TradeTransaction using long for timestamp, long for amount and double for price
typedef DynamicTradeTransaction<long, long, double> DynamicTradeTransactionT;

// Specialization of the visitor trait with an accept method for any visitor
template<>
struct visitor_traits<TradeTransactionT> {
    template <class VisitorType>
    static void accept(VisitorType &visitor, TradeTransactionT &item) noexcept {
        visitor.visit(item); // visit the item using the visit method in the visitor
    }
};

#endif //FTDP_TRADETRANSACTION_H
