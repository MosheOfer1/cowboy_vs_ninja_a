#include "Character.hpp"

namespace ariel
{
    Character::Character(std::string name, Point location, int attackPoints)
        : name(name), location(location), attackPoints(attackPoints) {}
    std::string Character::getName() const { return name; }
    Point Character::getLocation() const { return location; }
    int Character::getAttackPoints() const { return attackPoints; }
    bool Character::isAlive() const { return attackPoints > 0; }
    double Character::distance(Character *other) const { return location.distance(other->getLocation()); }
    void Character::hit(int harm)
    {
        attackPoints -= harm;
        if (attackPoints < 0)
        {
            attackPoints = 0;
        }
    }
    std::string Character::print() const
    {
        std::ostringstream oss;
        if (!isAlive())
        {
            oss << "(" << name << ")" << std::endl;
        }
        else
        {
            oss << name << " " << attackPoints << " " << location << std::endl;
        }
        return oss.str();
    }
}
