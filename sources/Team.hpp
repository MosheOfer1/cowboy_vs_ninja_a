#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Cowboy.hpp"
#include "Ninja.hpp"

namespace ariel {
    class Team {
    protected:
        std::vector<Cowboy*> cowboys;
        std::vector<Ninja*> ninjas;
        Character* leader;
    public:
        Team(Character* leader);
        ~Team();
        virtual void add(Character* character);
        virtual void attack(Team* enemy);
        virtual int stillAlive() const;
        virtual void print() const;
        // Additional methods
        virtual std::vector<Character*> getMembers();
        virtual std::vector<Character*> getAliveMembers(std::vector<Character*> &characters);
        virtual void attackVictim(Character *attacker, Character *victim);
    };

    class Team2 : public Team {
    private:
        std::vector<Character*> members;
    public:
        Team2(Character* leader);
        ~Team2();
        void add(Character* character) override;
        int stillAlive() const override;
        void print() const override;
        // Additional methods
        std::vector<Character*> getMembers() override;
        std::vector<Character*> getAliveMembers(std::vector<Character*> &characters) override;
        //void attackVictim(Character *attacker, Character *victim) override;
    };
}

#endif // TEAM_HPP
