#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Point.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YountNinja.hpp"
#include "TrainedNinja.hpp"

namespace ariel {
    class Team {
    private:
        std::vector<Character*> members;
    public:
        Team(Character* leader);
        ~Team();
        void add(Character* c);
        void attack(Team* enemy);
        int stillAlive() const;
        void print() const;
    };
}

#endif // TEAM_HPP
