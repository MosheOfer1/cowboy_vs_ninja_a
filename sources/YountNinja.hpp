#ifndef YOUNTNINJA_HPP
#define YOUNTNINJA_HPP

#include "Ninja.hpp"

namespace ariel {
    class YountNinja : public Ninja {
    public:
        YountNinja(std::string name, Point position);
        std::string Print() const override;
    };
}

#endif // YOUNTNINJA_HPP
