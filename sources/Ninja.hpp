#ifndef NINJA_HPP
#define NINJA_HPP

#include "Character.hpp"

namespace ariel
{
    class Ninja : public Character
    {
    protected:
        int speed;

    public:
        Ninja(std::string name, Point position, int attackPoints, int speed)
            : Character(name, position, attackPoints), speed(speed) {}
        std::string print() const override;
        void move(Character *target);
        void slash(Character *target);
    };

    class YoungNinja : public Ninja {
    public:
        YoungNinja(std::string name, Point position)
        : Ninja(name, position, 100, 14) {}
    };

    class TrainedNinja : public Ninja
    {
    public:
        TrainedNinja(std::string name, Point position)
            : Ninja(name, position, 120, 12) {}
    };

    class OldNinja : public Ninja
    {
    public:
        OldNinja(std::string name, Point position)
            : Ninja(name, position, 150, 8) {}
    };
}


#endif // NINJA_HPP
