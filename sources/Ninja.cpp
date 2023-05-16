#include "Ninja.hpp"
#define NINJA_HARM 31

namespace ariel
{
    std::string Ninja::print() const
    {
        std::ostringstream oss;
        oss << "N " << Character::print();
        return oss.str();
    }

    void Ninja::move(Character *target)
    {
        Point dest = target->getLocation();
        Point newLocation = getLocation().moveTowards(getLocation(), dest, speed);
        if(DEBUG)std::cout << getName() << " moves from (" << getLocation().getX() << "," << getLocation().getY() << ") to (" << newLocation.getX() << "," << newLocation.getY() << ")!" << std::endl;
        location = newLocation;
    }

    void Ninja::slash(Character *target)
    {
        if (!this->isAlive())
        {
            throw std::runtime_error("Dead characters can't attack!");
        }
        if (!target->isAlive())
        {
            throw std::runtime_error("Can't attack a dead character!");
        }
        if (target == this)
        {
            throw std::runtime_error("One cannot harm himself!");
        }
        double dist = location.distance(target->getLocation());
        if (dist <= 1)
        {
            if(DEBUG)std::cout << getName() << " slashes " << target->getName() << " and deals " << NINJA_HARM << " damage!" << std::endl;
            target->hit(NINJA_HARM);
        }
        else
        {
            if(DEBUG)std::cout << getName() << " tries to slash " << target->getName() << ", but is too far away!" << std::endl;
        }
    }
}
