#include "Cowboy.hpp"


namespace ariel
{
    Cowboy::Cowboy(std::string name, Point location) : Character(name, location, 100, 100, 11), bullets(6) {}
    std::string Cowboy::Print() const
    {
        std::stringstream ss;
        ss << getName() << " (Cowboy) is at (" << getLocation().getX() << "," << getLocation().getY() << ") with " << health << " health and " << bullets << " bullets.";
        return ss.str();
    }
    void Cowboy::shoot(Character *target)
    {
        if (bullets <= 0)
        {
            std::cout << getName() << " is out of bullets!" << std::endl;
        }
        else
        {
            double dist = location.distance(target->getLocation());
            if (dist <= 10)
            {
                std::cout << getName() << " shoots " << target->getName() << " and deals " << attackPoints << " damage!" << std::endl;
                target->hit(attackPoints);
            }
            else
            {
                std::cout << getName() << " tries to shoot " << target->getName() << ", but is too far away!" << std::endl;
            }
            bullets--;
        }
    }
    bool Cowboy::has_bullets() const
    {
        return bullets > 0;
    }
    void Cowboy::reload()
    {
        bullets = 6;
    }
}
