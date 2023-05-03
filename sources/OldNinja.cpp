#include "OldNinja.hpp"

namespace ariel
{
    OldNinja::OldNinja(std::string name, Point position)
        : Ninja(name, position, 60, 60, 8) {}

    std::string OldNinja::Print() const
    {
        std::stringstream ss;
        ss << getName() << " (Old Ninja) is at (" << getLocation().getX() << "," << getLocation().getY() << ") with " << health << " health.";
        return ss.str();
    }
}
