#ifndef FTDP_TRADETRAITS_H
#define FTDP_TRADETRAITS_H

#include <utility>

/*
 * Custom traits for trading use cases implementation
 */

// Maps a sequence of any type to the type void
// C++17(C++1z) already has this in type_traits
template<class...>
using void_t = void;

// Primary template declaration of trait
template <typename T, typename = void>
struct is_container: std::false_type {};

// Specialized declaration of trait for
template<typename T>
struct is_container<T, void_t<
        typename T::iterator, // needs to have iterator
        typename T::const_iterator, // needs to have const iterator
        typename T::value_type // needs to have a value type
>> : public std::true_type {};

// Primary template declaration of trait
template<class, class = void>
struct is_valid_stock : std::false_type { };

// Specialized declaration of trait for
template<class T>
struct is_valid_stock<T, void_t<
        decltype(&T::name), // needs to have name
        decltype(&T::dayHistories) // needs to have day histories
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_dayHistory : std::false_type { };

// Specialized declaration of trait for
template<class T>
struct is_valid_dayHistory<T, void_t<
        decltype(&T::dayNumber), // needs to have day number
        decltype(&T::daySummary),  // needs to have day summary
        decltype(&T::tradeTransactions)  // needs to have trade transactions
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_daySummary : std::false_type { };

// Specialized declaration of trait for day summary
template<class T>
struct is_valid_daySummary<T, void_t<
        decltype(&T::dayNumber),  // needs to have day number
        decltype(&T::openingPrice),  // needs to have opening price
        decltype(&T::lowestPrice),  // needs to have lowest price
        decltype(&T::highestPrice),  // needs to have highest price
        decltype(&T::closingPrice)  // needs to have closing price
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_tradeTransaction : std::false_type { };

// Specialized declaration of trait for trade transaction
template<class T>
struct is_valid_tradeTransaction<T, void_t<
        decltype(&T::timestamp), // needs to have timestamp
        decltype(&T::amount),  // needs to have amount
        decltype(&T::price)  // needs to have price
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_tradeTransactionInfo : std::false_type { };

// Specialized declaration of trait for trade transaction info
template<class T>
struct is_valid_tradeTransactionInfo<T, void_t<
        is_valid_tradeTransaction<T>,  // needs to have what the trade transactions has
        decltype(&T::stock)  // needs to have stock
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_tradeTransactionContainer : std::false_type { };

// Specialized declaration of trait for trade transaction container
template<class T>
struct is_valid_tradeTransactionContainer<T, void_t<
        is_container<T>,  // needs to be a container
        is_valid_tradeTransaction<typename T::value_type> // the type of the items in the container need to be valid trade transaction
>> : std::true_type { };

// Primary template declaration of trait
template<class, class = void>
struct is_valid_dayHistoryContainer : std::false_type { };

// Specialized declaration of trait for day history container
template<class T>
struct is_valid_dayHistoryContainer<T, void_t<
        is_container<T>,  // needs to be a container
        is_valid_dayHistory<typename T::value_type> // the type of the items in the container need to be valid day history
>> : std::true_type { };

#endif //FTDP_TRADETRAITS_H
