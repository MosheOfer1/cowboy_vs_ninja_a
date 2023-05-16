#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Point.hpp"
#define DEBUG 0
namespace ariel
{
    class Character
    {
    protected:
        std::string name;
        Point location;
        int attackPoints;
        bool inTeam = false;
    public:
        Character(std::string name, Point location, int attackPoints);
        virtual ~Character() = default;
        std::string getName() const;
        Point getLocation() const;
        int getAttackPoints() const;
        bool isAlive() const;
        double distance(Character *other) const;
        void hit(int harm);
        virtual std::string print() const;
        bool isInTeam() const { return inTeam; }
        void setInTeam(bool inTeam) { this->inTeam = inTeam; }
    };
}

#endif // CHARACTER_HPP
