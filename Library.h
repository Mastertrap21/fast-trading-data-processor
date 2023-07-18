#ifndef FTDP_ITEM_H
#define FTDP_ITEM_H

#include <type_traits>

// The common Visitor class
class Visitor {
public:
    // virtual destructor because we want the Visitor class to be polymorphic
    virtual ~Visitor() {}
};

// Templated common Item class with a VisitorType which is also a template class
// like for example: DynamicVisitor<Item>
template <template<class> class VisitorType>
class Item {
public:
    // virtual accept function for any visitor of type Visitor
    virtual void accept(Visitor &visitor) noexcept = 0;
    // templated function for accepting a visitor for a specific type item
    template <class Type>
    void acceptVisitor(Type &item, Visitor &visitor) noexcept {
        // dynamic casting the visitor for this type so we get the right visit method using the accept method
        dynamic_cast<VisitorType<Type>&>(visitor).visit(item); // this is where the magic of dynamic polymorphism happens
    }
};

// Dynamic visitor class interface that implement the common visitor
// As we are going to implement this class multiple times for each specific type, in order to avoid the diamond death of multiple inheritance we need to make the inheritance virtual
template <class Type>
class DynamicVisitor : virtual public Visitor {
    // Let's make sure that the Type is subclass of Item<DynamicVisitor> such that it has an accept method that will call the visit method in this class
    static_assert(std::is_base_of<Item<DynamicVisitor>, Type>::value, "Type is not subclass of Item");
public:
    // The visit method for a generic Type
    // As this class will be implemented for each accepted Item type, it will provide virtual visit functions for all the accepted types
    virtual void visit(Type &item) noexcept = 0;
};

// Primary template declaration of the visitor_traits
// The specializations for this with the right accept method in it will be provided by the user for each accepted type
template<class Type>
struct visitor_traits {
    template<class VisitorType>
    // A dummy implementation of accept method
    static void accept(VisitorType &visitor, Type &item) noexcept {
        // Do nothing, because accept method is not implemented for this type
        // Could as well throw exception or terminate
    }
};

// The static visitor class which implements the common Visitor interface
class StaticVisitor : public Visitor {
    // Templated visit function for visiting any type of the accepted item types
    template <class Type>
    void visit(Type &item) noexcept {
        return Type::visit(&item);
    }
};

#endif //FTDP_ITEM_H
