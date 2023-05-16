#include "Team.hpp"
#include <algorithm>
#include <limits>

namespace ariel
{
    Team2::Team2(Character *leader) : Team(leader) {
        if(DEBUG)std::cout << "2" << std::endl;
        cowboys.clear();
        ninjas.clear();
        leader->setInTeam(false);
        add(leader);
    }

    Team2::~Team2()
    {
        for (auto member : members)
        {
            delete member;
        }
    }

    void Team2::add(Character *character)
    {
        if (character->isInTeam())
        {
            throw std::runtime_error(character->getName() + " is already in a team!");
        }
        if(DEBUG)std::cout << character->getName() << "2" << std::endl;
        if (members.size() >= 10)
        {
            throw std::runtime_error("The team is full, cannot add more members!");
        }
        if (std::find(members.begin(), members.end(), character) != members.end())
        {
            throw std::runtime_error(character->getName() + " is already in the team!");
        }
        members.push_back(character);
        character->setInTeam(true);
    }

    std::vector<Character *> Team2::getMembers()
    {
        return members;
    }

    std::vector<Character *> Team2::getAliveMembers(std::vector<Character *> &characters)
    {
        std::vector<Character *> aliveMembers;
        for (auto character : characters)
        {
            if (character->isAlive())
            {
                aliveMembers.push_back(character);
            }
        }
        return aliveMembers;
    }

    int Team2::stillAlive() const
    {
        int count = 0;
        for (auto member : members)
        {
            if (member->isAlive())
            {
                count++;
            }
        }
        return count;
    }

    void Team2::print() const
    {
        if(DEBUG)std::cout << "Team members:" << std::endl;
        for (auto member : members)
        {
            if(DEBUG)std::cout << "    " << member->print() << std::endl;
        }
    }
}
