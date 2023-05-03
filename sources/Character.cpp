#include "Character.hpp"

namespace ariel
{
    Character::Character(std::string name, Point location, int health, int maxHealth, int attackPoints)
        : name(name), location(location), health(health), maxHealth(maxHealth), attackPoints(attackPoints) {}
    std::string Character::getName() const { return name; }
    Point Character::getLocation() const { return location; }
    bool Character::isAlive() const { return health > 0; }
    double Character::distance(Character *other) const { return location.distance(other->getLocation()); }
    void Character::hit(int harm)
    {
        health -= harm;
        if (health < 0)
        {
            health = 0;
        }
    }
}
