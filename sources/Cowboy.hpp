#ifndef COWBOY_HPP
#define COWBOY_HPP

#include "Character.hpp"

namespace ariel {
    class Cowboy : public Character {
    private:
        int bullets;
    public:
        Cowboy(std::string name, Point location);
        std::string Print() const override;
        void shoot(Character* target);
        bool has_bullets() const;
        void reload();

    };
}

#endif // COWBOY_HPP
