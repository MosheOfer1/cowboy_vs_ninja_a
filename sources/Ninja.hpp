#ifndef NINJA_HPP
#define NINJA_HPP

#include "Character.hpp"

namespace ariel {
    class Ninja : public Character {
    protected:
        int speed;
    public:
        Ninja(std::string name, Point position, int health, int maxHealth, int attackPoints);
        std::string Print() const override;
        void move(Character* target);
        void slash(Character* target);
    };
}

#endif // NINJA_HPP
