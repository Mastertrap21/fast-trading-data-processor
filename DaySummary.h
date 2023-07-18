#ifndef FTDP_DAYSUMMARY_H
#define FTDP_DAYSUMMARY_H

#include <limits>

template <class DayNumber, class Price>
class DaySummary {
public:
    static_assert(std::is_arithmetic<DayNumber>::value, "DayNumber type is not valid"); // make sure at compile time that DayNumber is valid
    static_assert(std::is_arithmetic<Price>::value, "Price type is not valid"); // make sure at compile time that Price is valid
    DayNumber dayNumber;
    Price openingPrice;
    Price lowestPrice{std::numeric_limits<Price>::max()}; // default to max
    Price highestPrice{std::numeric_limits<Price>::min()}; // default to min
    Price closingPrice;
    DaySummary(const DaySummary& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DaySummary& operator=(const DaySummary&) = delete; // remove the copy assignment, we don't want to copy information as the dataset is very large
    DaySummary(DayNumber dayNumber) : dayNumber(dayNumber) { }; // initialization list / universal constructor
};

template <class DayNumber, class Price>
class DynamicDaySummary : public DaySummary<DayNumber, Price>, public Item<DynamicVisitor> {
public:
    DynamicDaySummary(const DynamicDaySummary& that) = delete; // remove the copy constructor, we don't want to copy information as the dataset is very large
    DynamicDaySummary& operator=(const DynamicDaySummary&) = delete; // remove the copy assignment, we don't want to copy information as the dataset is very large
    DynamicDaySummary(DayNumber dayNumber) :
        DaySummary<DayNumber, Price>::DaySummary(dayNumber) { }; // initialization list / universal constructor
    // Accept method implementation because this is the dynamic daySummary structures which will be used by the Dynamic visitors
    void accept(Visitor &visitor) noexcept override {
        acceptVisitor(*this, visitor);
    };
};

// Type definition for DaySummary using integer for day number and double for price
typedef DaySummary<int, double> DaySummaryT;
// Type definition for dynamic DaySummary  using integer for day number and double for price
typedef DynamicDaySummary<int, double> DynamicDaySummaryT;

// Specialization of the visitor trait with an accept method for any visitor
template<>
struct visitor_traits<DaySummaryT> {
    template <class VisitorType>
    static void accept(VisitorType &visitor, DaySummaryT &item) noexcept {
        visitor.visit(item); // visit the item using the visit method in the visitor
    }
};

#endif //FTDP_DAYSUMMARY_H
