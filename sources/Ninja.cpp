#include "Ninja.hpp"

namespace ariel
{
    Ninja::Ninja(std::string name, Point position, int health, int maxHealth, int attackPoints)
        : Character(name, position, health, maxHealth, attackPoints), speed(10) {}

    std::string Ninja::Print() const
    {
        std::stringstream ss;
        ss << getName() << " (Ninja) is at (" << getLocation().getX() << "," << getLocation().getY() << ") with " << health << " health and speed of " << speed << ".";
        return ss.str();
    }

    void Ninja::move(Character *target)
    {
        Point dest = target->getLocation();
        Point newLocation = getLocation().moveTowards(getLocation(), dest, speed);
        std::cout << getName() << " moves from (" << getLocation().getX() << "," << getLocation().getY() << ") to (" << newLocation.getX() << "," << newLocation.getY() << ")!" << std::endl;
        location = newLocation;
    }

    void Ninja::slash(Character *target)
    {
        double dist = location.distance(target->getLocation());
        if (dist <= 2)
        {
            std::cout << getName() << " slashes " << target->getName() << " and deals " << attackPoints << " damage!" << std::endl;
            target->hit(attackPoints);
        }
        else
        {
            std::cout << getName() << " tries to slash " << target->getName() << ", but is too far away!" << std::endl;
        }
    }
}
