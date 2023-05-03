#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP

#include "Ninja.hpp"

namespace ariel {
    class OldNinja : public Ninja {
    public:
        OldNinja(std::string name, Point position);
        std::string Print() const override;
    };
}

#endif // OLDNINJA_HPP
