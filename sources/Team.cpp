#include "Team.hpp"
#include <algorithm>
#include <limits>

namespace ariel
{
    Team::Team(Character *leader) : leader(leader)
    {
        if(DEBUG)std::cout << "1" << std::endl;
        add(leader);
    }

    Team::~Team()
    {
        for (auto cowboy : cowboys)
        {
            delete cowboy;
        }
        for (auto ninja : ninjas)
        {
            delete ninja;
        }
    }

    void Team::add(Character *character)
    {
        if (character->isInTeam())
        {
            throw std::runtime_error(character->getName() + " is already in a team!");
        }
        if(DEBUG)std::cout << character->getName() << "1" << std::endl;
        if (cowboys.size() + ninjas.size() >= 10)
        {
            throw std::runtime_error("The team is full, cannot add more members!");
        }

        if (auto cowboy = dynamic_cast<Cowboy *>(character))
        {
            if (std::find(cowboys.begin(), cowboys.end(), cowboy) != cowboys.end())
            {
                throw std::runtime_error(cowboy->getName() + " is already in the team!");
            }
            cowboys.push_back(cowboy);
        }
        else if (auto ninja = dynamic_cast<Ninja *>(character))
        {
            if (std::find(ninjas.begin(), ninjas.end(), ninja) != ninjas.end())
            {
                throw std::runtime_error(ninja->getName() + " is already in the team!");
            }
            ninjas.push_back(ninja);
        }
        character->setInTeam(true);
    }

    Character *findClosest(std::vector<Character *> &members, Character *leader)
    {
        double closestDist = std::numeric_limits<double>::max();
        Character *closestCharacter = nullptr;

        for (auto member : members)
        {
            if (member->isAlive())
            {
                double dist = leader->distance(member);
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestCharacter = member;
                }
            }
        }
        return closestCharacter;
    }

    std::vector<Character *> Team::getMembers()
    {
        std::vector<Character *> allMembers;
        allMembers.insert(allMembers.end(), cowboys.begin(), cowboys.end());
        allMembers.insert(allMembers.end(), ninjas.begin(), ninjas.end());
        return allMembers;
    }

    std::vector<Character *> Team::getAliveMembers(std::vector<Character *> &characters)
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

    void Team::attackVictim(Character *attacker, Character *victim)
    {
        if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker))
        {
            // Cowboys who have bullets in their guns will shoot the victim
            if (cowboy->hasboolets())
            {
                cowboy->shoot(victim);
            }
            else
            {
                // Cowboys who don't have bullets will load their weapons
                cowboy->reload();
            }
        }
        else if (Ninja *ninja = dynamic_cast<Ninja *>(attacker))
        {
            // Ninjas within 1 meter of the victim will hit the victim,
            // and ninjas further away will advance towards the victim
            double dist = ninja->distance(victim);
            if (dist <= 1.0)
            {
                ninja->slash(victim);
            }
            else
            {
                ninja->move(victim);
            }
        }
    }

    void Team::attack(Team *enemy)
    {
        if (enemy == nullptr)
        {
            throw std::invalid_argument("Enemy team can't be null!");
        }
        //print();
        //enemy->print();
        // Get all members of both teams
        std::vector<Character *> allMembers = getMembers();
        std::vector<Character *> allEnemyMembers = enemy->getMembers();
        // std::vector<Character *> enemyAliveMembers = getAliveMembers(allEnemyMembers);
        std::vector<Character *> aliveMembers = getAliveMembers(allMembers);

        // Check if the attacking team has a living leader
        if (!leader->isAlive())
        {
            // Find the living character closest to the dead leader
            Character *closestMember = findClosest(allMembers, leader);
            // If a living member is found, set them as the new leader
            if (closestMember != nullptr)
            {
                leader = closestMember;
            }
            else
            {
                // If there are no living members left, the attack is over
                return;
            }
        }

        for (auto attacker : aliveMembers)
        {
            // Update the list of alive members in the enemy team
            std::vector<Character *> enemyAliveMembers = getAliveMembers(allEnemyMembers);

            // Choose a victim from the enemy group that stands close to the leader
            Character *victim = findClosest(enemyAliveMembers, leader);
            if (victim == nullptr)
            {
                // No living members in enemy team, return from function
                return;
            }
            if(DEBUG)std::cout << victim->getName() << " is the victim of " << leader->getName() << " team's" << std::endl;

            attackVictim(attacker, victim);
        }
    }

    int Team::stillAlive() const
    {
        int count = 0;
        for (auto cowboy : cowboys)
        {
            if (cowboy->isAlive())
            {
                count++;
            }
        }
        for (auto ninja : ninjas)
        {
            if (ninja->isAlive())
            {
                count++;
            }
        }
        return count;
    }

    void Team::print() const
    {
        if(DEBUG)std::cout << "Team members cowboys and ninjas:" << std::endl;
        for (auto cowboy : cowboys)
        {
            if(DEBUG)std::cout << "    " << cowboy->print() << std::endl;
        }
        for (auto ninja : ninjas)
        {
            if(DEBUG)std::cout << "    " << ninja->print() << std::endl;
        }
    }
}