#include "YountNinja.hpp"

namespace ariel
{
    YountNinja::YountNinja(std::string name, Point position)
        : Ninja(name, position, 70, 70, 10) {}

    std::string YountNinja::Print() const
    {
        std::stringstream ss;
        ss << getName() << " (Young Ninja) is at (" << getLocation().getX() << "," << getLocation().getY() << ") with " << health << " health and speed of " << speed << ".";
        return ss.str();
    }
}
