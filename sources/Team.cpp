#include "Team.hpp"
#include <algorithm>
#include <limits>

namespace ariel {
    Team::Team(Character* leader) {
        members.push_back(leader);
    }

    Team::~Team() {
        for (auto member : members) {
            delete member;
        }
    }

    void Team::add(Character* Character) {
        if (std::find(members.begin(), members.end(), Character) != members.end()) {
            throw std::runtime_error(Character->getName() + " is already in the team!");
        }
        members.push_back(Character);
    }

    void Team::attack(Team* enemy) {
        // Check if the attacking team has a living leader
        Character* leader = members[0];
        if (!leader->isAlive()) {
            // Find the living character closest to the dead leader
            double closestDist = std::numeric_limits<double>::max();
            Character* closestMember = nullptr;
            for (auto member : members) {
                if (member->isAlive()) {
                    double dist = leader->distance(member);
                    if (dist < closestDist) {
                        closestDist = dist;
                        closestMember = member;
                    }
                }
            }
            // If a living member is found, set them as the new leader
            if (closestMember != nullptr) {
                leader = closestMember;
            } else {
                // If there are no living members left, the attack is over
                return;
            }
        }

        // Choose a victim from the enemy group
        double closestDist = std::numeric_limits<double>::max();
        Character* victim = nullptr;
        for (auto enemyMember : enemy->members) {
            if (enemyMember->isAlive()) {
                double dist = leader->distance(enemyMember);
                if (dist < closestDist) {
                    closestDist = dist;
                    victim = enemyMember;
                }
            }
        }

        // If there are no living members left in the enemy group, the attack is over
        if (victim == nullptr) {
            return;
        }

        // All living members of the attacking group will attack the chosen victim
        for (auto attacker : members) {
            if (attacker->isAlive()) {
                if (Cowboy* cowboy = dynamic_cast<Cowboy*>(attacker)) {
                    // Cowboys who have bullets in their guns will shoot the victim
                    if (cowboy->has_bullets()) {
                        cowboy->shoot(victim);
                    } else {
                        // Cowboys who don't have bullets will load their weapons
                        cowboy->reload();
                    }
                } else if (Ninja* ninja = dynamic_cast<Ninja*>(attacker)) {
                    // Ninjas within 1 meter of the victim will kill the victim,
                    // and ninjas further away will advance towards the victim
                    double dist = ninja->distance(victim);
                    if (dist <= 1.0) {
                        ninja->slash(victim);
                    } else {
                        ninja->move(victim);
                    }
                }
            }
        }

        // If the victim is dead, choose a new victim
        if (!victim->isAlive()) {
            attack(enemy);
        }
    }

    int Team::stillAlive() const {
        int count = 0;
        for (auto member : members) {
            if (member->isAlive()) {
                count++;
            }
        }
        return count;
    }

    void Team::print() const {
        std::cout << "Team members:" << std::endl;
        for (auto member : members) {
            std::cout << "    " << member->Print() << std::endl;
        }
    }
}