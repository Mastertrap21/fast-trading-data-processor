#ifndef FTDP_READABLETRADESTRUCTURES_H
#define FTDP_READABLETRADESTRUCTURES_H

#include <type_traits>

#include "Library.h"

#pragma pack(push, 1)
template <typename Timestamp, typename Stock, typename Amount, typename Price>
struct TradeTransactionInfo {
    static_assert(std::is_integral<Timestamp>::value, "Timestamp type is not valid"); // make sure at compile time that Timestamp is valid
    static_assert(std::is_arithmetic<Amount>::value, "Amount type is not valid"); // make sure at compile time that Amount is valid
    static_assert(std::is_floating_point<Price>::value, "Price type is not valid"); // make sure at compile time that Price is valid
public:
    Timestamp timestamp;
    Stock stock;
    Amount amount;
    Price price;
};
#pragma pack(pop)

template <typename Timestamp, typename Stock, typename Amount, typename Price>
struct DynamicTradeTransactionInfo : public TradeTransactionInfo<Timestamp, Stock, Amount, Price>, public Item<DynamicVisitor> {
    static_assert(std::is_integral<Timestamp>::value, "Timestamp type is not valid"); // make sure at compile time that Timestamp is valid
    static_assert(std::is_arithmetic<Amount>::value, "Amount type is not valid"); // make sure at compile time that Amount is valid
    static_assert(std::is_floating_point<Price>::value, "Price type is not valid"); // make sure at compile time that Price is valid
public:
    // constructor using fields
    DynamicTradeTransactionInfo(Timestamp timestamp, Amount amount, Price price){
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::timestamp = timestamp;
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::amount = amount;
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::price = price;
    };
    // Accept method implementation because this is the dynamic DynamicTradeTransactionInfo structures which will be used by the Dynamic visitors
    void accept(Visitor &visitor) noexcept override {
        acceptVisitor(*this, visitor);
    };
};

template <typename Timestamp, typename Stock, typename Amount, typename Price>
struct StaticTradeTransactionInfo : public TradeTransactionInfo<Timestamp, Stock, Amount, Price> {
    static_assert(std::is_integral<Timestamp>::value, "Timestamp type is not valid"); // make sure at compile time that Timestamp is valid
    static_assert(std::is_arithmetic<Amount>::value, "Amount type is not valid"); // make sure at compile time that Amount is valid
    static_assert(std::is_floating_point<Price>::value, "Price type is not valid"); // make sure at compile time that Price is valid
public:
    // constructor using fields
    StaticTradeTransactionInfo(Timestamp timestamp, Amount amount, Price price){
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::timestamp = timestamp;
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::amount = amount;
        TradeTransactionInfo<Timestamp, Stock, Amount, Price>::price = price;
    };
};

// Type definition for readable TradeTransactionInfo using long as timestamp, char[20] as stock name, long as amount and double as price
typedef TradeTransactionInfo<long, char[20], long, double> TradeTransactionInfoT;
// Type definition for static TradeTransactionInfo using long as timestamp, char[20] as stock name, long as amount and double as price
typedef StaticTradeTransactionInfo<long, char[20], long, double> StaticTradeTransactionInfoT;
// Type definition for dynamic TradeTransactionInfo using long as timestamp, char[20] as stock name, long as amount and double as price
typedef DynamicTradeTransactionInfo<long, char[20], long, double> DynamicTradeTransactionInfoT;

// Specialization of the visitor trait with an accept method for any visitor
template<>
struct visitor_traits<TradeTransactionInfoT> {
    template<class VisitorType>
    static void accept(VisitorType &visitor, TradeTransactionInfoT &item) noexcept {
        visitor.visit(item); // visit the item using the visit method in the visitor
    }
};

#endif //FTDP_READABLETRADESTRUCTURES_H
