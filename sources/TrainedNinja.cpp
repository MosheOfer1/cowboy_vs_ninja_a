#include "TrainedNinja.hpp"

namespace ariel
{
    TrainedNinja::TrainedNinja(std::string name, Point position)
        : Ninja(name, position, 80, 80, 12) {}

    std::string TrainedNinja::Print() const
    {
        std::stringstream ss;
        ss << getName() << " (Trained Ninja) is at (" << getLocation().getX() << "," << getLocation().getY() << ") with " << health << " health and speed of " << speed << ".";
        return ss.str();
    }
}
