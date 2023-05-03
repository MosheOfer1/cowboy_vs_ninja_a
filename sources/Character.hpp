#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Point.hpp"

namespace ariel
{
    class Character
    {
    protected:
        std::string name;
        Point location;
        int health;
        int maxHealth;
        int attackPoints;

    public:
        Character(std::string name, Point location, int health, int maxHealth, int attackPoints);
        virtual ~Character() = default;
        std::string getName() const;
        Point getLocation() const;
        bool isAlive() const;
        double distance(Character *other) const;
        void hit(int harm);
        virtual std::string Print() const = 0;
    };
}

#endif // CHARACTER_HPP
