#include "doctest.h"
#include "sources/Team.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>

using namespace ariel;

TEST_CASE("Testing Point class and moveTowards function edge cases")
{
    const double epsilon = 0.000000000001;
    Point src(0, 0);
    Point dest(10, 10);
    Point p;
    CHECK_NOTHROW(p.print());

    std::stringstream buffer;
    buffer << "(" << dest.getX() << ", " << dest.getY() << ")" << std::endl;
    CHECK(buffer.str() == std::string("(10, 10)\n"));

    // Test case 1: distance between src and dest is equal to dist
    double dist1 = src.distance(dest);
    p = src.moveTowards(src, dest, dist1);
    CHECK(p.distance(dest) <= epsilon);

    // Test case 2: distance between src and dest is less than dist
    double dist2 = src.distance(dest) * 1.5;
    p = src.moveTowards(src, dest, dist2);
    CHECK(p.distance(dest) <= epsilon);

    // Test case 3: distance between src and dest is greater than dist
    double dist3 = src.distance(dest) / 2;
    p = src.moveTowards(src, dest, dist3);
    CHECK(fabs(p.distance(src) - dist3) <= epsilon);

    // Test case 4: src and dest have the same coordinates
    Point same(5, 5);
    double dist4 = 3.0;
    p = same.moveTowards(same, same, dist4);
    CHECK(p.distance(same) <= epsilon);
}

TEST_CASE("Testing Cowboy class and its functions")
{
    std::unique_ptr<Cowboy> cowboy1 = std::make_unique<Cowboy>("Cowboy1", Point(0, 0));
    std::unique_ptr<Cowboy> cowboy2 = std::make_unique<Cowboy>("Cowboy2", Point(8, 0));
    std::unique_ptr<Cowboy> cowboy3 = std::make_unique<Cowboy>("Cowboy3", Point(12, 0));

    CHECK(cowboy1->getName() == "Cowboy1");
    CHECK(cowboy1->isAlive() == true);
    CHECK(cowboy1->distance(cowboy2.get()) == 8);
    CHECK(cowboy1->hasboolets() == true);

    // Cowboy1 shoots Cowboy2, who is within range.
    cowboy1->shoot(cowboy2.get());
    CHECK(cowboy2->isAlive() == true);
    CHECK(cowboy2->getAttackPoints() == 100);

    // Cowboy1 shoots Cowboy3, who is out of range.
    cowboy1->shoot(cowboy3.get());
    CHECK(cowboy3->isAlive() == true);
    CHECK(cowboy3->getAttackPoints() == 110);

    // Cowboy1 uses all bullets and tries to shoot.
    cowboy1->reload();
    for (int i = 0; i < 6; ++i)
    {
        cowboy1->shoot(cowboy2.get());
    }
    CHECK(cowboy1->hasboolets() == false);
    // Before
    CHECK(cowboy2->getAttackPoints() == 40);
    // Try to shoot
    cowboy1->shoot(cowboy2.get());
    // No harm
    CHECK(cowboy2->getAttackPoints() == 40);

    // Cowboy1 reloads and shoots Cowboy2 again.
    cowboy1->reload();
    CHECK(cowboy1->hasboolets() == true);
    cowboy1->shoot(cowboy2.get());
    CHECK(cowboy2->isAlive() == true);
    CHECK(cowboy2->getAttackPoints() == 30);

    // Cowboy1 shoots at themselves.
    CHECK_THROWS_AS(cowboy1->shoot(cowboy1.get()), std::runtime_error);
    CHECK(cowboy1->isAlive() == true);
    CHECK(cowboy1->getAttackPoints() == 110);

    // Test with cowboys at diagonal locations.
    std::unique_ptr<Cowboy> cowboy4 = std::make_unique<Cowboy>("Cowboy4", Point(3, 4));
    // Pythagoras 3^2 + 4^2 = 5^2
    CHECK(cowboy1->distance(cowboy4.get()) == 5);

    // Test if cowboy can die.
    while(cowboy2.get()->isAlive())
    {
        cowboy1->shoot(cowboy2.get());
    }
    CHECK(cowboy2->isAlive() == false);

    // Call the print function
    CHECK(cowboy2->print() == "C (Cowboy2)\n");
    CHECK(cowboy1->print() == "C Cowboy1 110 (0,0)\n");
}

TEST_CASE("Testing Ninja class and its functions")
{
    std::unique_ptr<Ninja> ninja1 = std::make_unique<YoungNinja>("Ninja1", Point(0, 0));
    std::unique_ptr<Ninja> ninja2 = std::make_unique<TrainedNinja>("Ninja2", Point(1, 0));
    std::unique_ptr<Ninja> ninja3 = std::make_unique<OldNinja>("Ninja3", Point(2, 0));

    CHECK(ninja1->getName() == "Ninja1");
    CHECK(ninja1->isAlive() == true);
    CHECK(ninja1->distance(ninja2.get()) == 1);

    // Ninja1 slashes Ninja2, who is within range.
    ninja1->slash(ninja2.get());
    CHECK(ninja2->isAlive() == true);
    CHECK(ninja2->getAttackPoints() == 89);

    // Ninja1 slashes Ninja3, who is out of range.
    ninja1->slash(ninja3.get());
    CHECK(ninja3->isAlive() == true);
    CHECK(ninja3->getAttackPoints() == 150);

    // Ninja1 moves closer to Ninja3 and slashes.
    ninja1->move(ninja3.get());
    CHECK(ninja1->getLocation().distance(ninja3->getLocation()) <= 1);
    ninja1->slash(ninja3.get());
    CHECK(ninja3->isAlive() == true);
    CHECK(ninja3->getAttackPoints() == 119);

    // Ninja1 slashes themselves.
    CHECK_THROWS_AS(ninja1->slash(ninja1.get()), std::runtime_error);
    CHECK(ninja1->isAlive() == true);
    CHECK(ninja1->getAttackPoints() == 100);

    // Test if cowboy can kill ninja
    std::unique_ptr<Cowboy> cowboy1 = std::make_unique<Cowboy>("Cowboy1", Point(1, 0));
    while (ninja2->isAlive())
    {
        cowboy1->shoot(ninja2.get());
        if (!cowboy1->hasboolets())
        {
            cowboy1->reload();
        }
    }

    // Test if ninja can kill ninja
    while (ninja3->isAlive())
    {
        ninja1->slash(ninja3.get());
    }

    CHECK_FALSE(ninja2->isAlive());
    CHECK_FALSE(ninja3->isAlive());

    // Call the print function and see if they died
    CHECK(ninja2->print() == "N (Ninja2)\n");
    CHECK(ninja1->print() == "N Ninja1 100 (2,0)\n");
    CHECK(ninja3->print() == "N (Ninja3)\n");
}

TEST_CASE("Testing Ninja class and its functions")
{
    std::unique_ptr<Ninja> youngNinja = std::make_unique<YoungNinja>("YoungNinja", Point(0, 0));
    std::unique_ptr<Ninja> trainedNinja = std::make_unique<TrainedNinja>("TrainedNinja", Point(10, 10));
    std::unique_ptr<Ninja> oldNinja = std::make_unique<OldNinja>("OldNinja", Point(20, 20));
    std::unique_ptr<Cowboy> cowboy = std::make_unique<Cowboy>("Cowboy", Point(30, 30));

    // Check initial health
    CHECK(youngNinja->getAttackPoints() == 100);
    CHECK(trainedNinja->getAttackPoints() == 120);
    CHECK(oldNinja->getAttackPoints() == 150);

    // Check initial location
    CHECK(youngNinja->getLocation().getX() == 0);
    CHECK(youngNinja->getLocation().getY() == 0);
    CHECK(trainedNinja->getLocation().getX() == 10);
    CHECK(trainedNinja->getLocation().getY() == 10);
    CHECK(oldNinja->getLocation().getX() == 20);
    CHECK(oldNinja->getLocation().getY() == 20);

    // Check names
    CHECK(youngNinja->getName() == "YoungNinja");
    CHECK(trainedNinja->getName() == "TrainedNinja");
    CHECK(oldNinja->getName() == "OldNinja");

    // Call the print function
    CHECK(youngNinja->print() == "N YoungNinja 100 (0,0)\n");
    CHECK(trainedNinja->print() == "N TrainedNinja 120 (10,10)\n");
    CHECK(oldNinja->print() == "N OldNinja 150 (20,20)\n");

    // Check distance
    CHECK(youngNinja->distance(cowboy.get()) == doctest::Approx(42.4264).epsilon(0.001));
    CHECK(trainedNinja->distance(cowboy.get()) == doctest::Approx(28.2843).epsilon(0.001));
    CHECK(oldNinja->distance(cowboy.get()) == doctest::Approx(14.1421).epsilon(0.001));

    youngNinja->move(cowboy.get());
    youngNinja->move(cowboy.get());
    youngNinja->move(cowboy.get());
    // Cowboy causes 10 damage per hit.
    for (int i = 0; i < 10; ++i)
    {
        if (!cowboy->hasboolets())
        {
            cowboy->reload();
        }

        cowboy->shoot(youngNinja.get()); // Cowboy inflicts damage to YoungNinja.
        if (youngNinja->isAlive())
        {
            CHECK(youngNinja->getAttackPoints() == 100 - (i + 1) * 10);
        }
        else
        {
            CHECK(youngNinja->getAttackPoints() <= 0);
            break;
        }
    }

    CHECK(youngNinja->isAlive() == false);
}

TEST_CASE("Testing Team class and its attack function")
{
    // Setup the teams
    YoungNinja *ninja1 = new YoungNinja("Ninja1", Point(0, 0));
    OldNinja *ninja2 = new OldNinja("Ninja2", Point(1, 0));
    Cowboy *cowboy1 = new Cowboy("Cowboy1", Point(2, 0));
    Cowboy *cowboy2 = new Cowboy("Cowboy2", Point(3, 0));

    Team team1(ninja1);
    team1.add(ninja2);

    Team team2(cowboy1);
    team2.add(cowboy2);

    // Initial checks
    CHECK(team1.stillAlive() == 2);
    CHECK(team2.stillAlive() == 2);

    // Attack round 1
    team1.attack(&team2);

    // Check results of first round
    CHECK(team1.stillAlive() == 2);
    CHECK(team2.stillAlive() == 2); // Assuming cowboys are still alive after first attack

    // Attack round 2
    team2.attack(&team1);

    // Check results of second round
    CHECK(team1.stillAlive() > 0);  // At least one ninja should still be alive
    CHECK(team2.stillAlive() == 2); // Cowboys should still be alive

    // Continue the fight until only one team remains
    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {
        team1.attack(&team2);
        if (team2.stillAlive() > 0)
        {
            team2.attack(&team1);
        }
    }

    // Check the final result
    if (team1.stillAlive() > 0)
    {
        CHECK(team2.stillAlive() == 0);
    }
    else
    {
        CHECK(team2.stillAlive() > 0);
    }
}

TEST_CASE("Testing Team class, attacking the closest victim")
{
    // Setup a team
    Cowboy *cowboy = new Cowboy("Cowboy", Point(0, 0));
    Team team(cowboy);

    // Add more members
    for (int i = 0; i < 9; ++i)
    { // 9 + 1 (original leader) = 10
        team.add(new TrainedNinja("Ninja" + std::to_string(i + 1), Point(6, 0)));
    }

    // Try to add one more member, should throw an exception
    bool exceptionThrown = false;
    try
    {
        team.add(new TrainedNinja("Ninja11", Point(10, 0)));
    }
    catch (const std::runtime_error &e)
    {
        exceptionThrown = true;
    }
    CHECK(exceptionThrown);

    // Setup an enemy team
    Cowboy *enemyCowboy = new Cowboy("EnemyCowboy", Point(20, 0)); // Far from the attacking team
    Cowboy *closerEnemy = new Cowboy("CloserEnemy", Point(5, 0));  // Closer to the attacking team
    Team enemyTeam(closerEnemy);
    enemyTeam.add(enemyCowboy);

    // Attack enemy
    team.attack(&enemyTeam);

    // Check that the right victim was chosen: it should be the member of the enemy team who is closer to the attacking team's leader
    CHECK(enemyCowboy->isAlive() == true);  // Far enemy should still be alive
    CHECK(closerEnemy->isAlive() == false); // Close enemy should be attacked and not alive
}

TEST_CASE("Testing Cowboy reload and Ninja move")
{
    // Setup the characters
    ariel::Cowboy *cowboy1 = new ariel::Cowboy("Cowboy1", Point(0, 0));
    ariel::Cowboy *cowboy2 = new ariel::Cowboy("Cowboy2", Point(10, 10));
    ariel::Ninja *ninja1 = new ariel::OldNinja("Ninja1", Point(0, 0));
    ariel::Ninja *ninja2 = new ariel::OldNinja("Ninja2", Point(10, 10));

    // Setup the teams
    ariel::Team team1(cowboy1);
    team1.add(cowboy2);

    ariel::Team team2(ninja1);
    team2.add(ninja2);

    // Make sure the cowboy has no bullets
    while (cowboy1->hasboolets())
    {
        cowboy1->shoot(ninja2);
    }

    // Attack round 1
    team1.attack(&team2);

    // Check that the cowboy has reloaded
    CHECK(cowboy1->hasboolets() == true);

    // Check that the ninja has moved towards the cowboy
    double distAfterMove = ninja1->getLocation().distance(cowboy1->getLocation());
    CHECK(distAfterMove < 10.0);
}

TEST_CASE("Testing Ninja movement speed")
{
    // The right speeds
    int YSpeed = 14, TSpeed = 12, OSpeed = 8;

    Character *target = new Cowboy("Cowboy", Point(20, 20));

    Ninja *youngNinja = new YoungNinja("YoungNinja", Point(0, 0));
    double youngNinjaOriginalDistance = youngNinja->distance(target);
    youngNinja->move(target);
    double youngNinjaNewDistance = youngNinja->distance(target);
    CHECK(std::abs(youngNinjaOriginalDistance - youngNinjaNewDistance - YSpeed) < 0.001);
    delete youngNinja;

    Ninja *trainedNinja = new TrainedNinja("TrainedNinja", Point(0, 0));
    double trainedNinjaOriginalDistance = trainedNinja->distance(target);
    trainedNinja->move(target);
    double trainedNinjaNewDistance = trainedNinja->distance(target);
    CHECK(std::abs(trainedNinjaOriginalDistance - trainedNinjaNewDistance - TSpeed) < 0.001);
    delete trainedNinja;

    Ninja *oldNinja = new OldNinja("OldNinja", Point(0, 0));
    double oldNinjaOriginalDistance = oldNinja->distance(target);
    oldNinja->move(target);
    double oldNinjaNewDistance = oldNinja->distance(target);
    CHECK(std::abs(oldNinjaOriginalDistance - oldNinjaNewDistance - OSpeed) < 0.001);
    delete oldNinja;

    delete target;
}

TEST_CASE("Testing teams")
{
    // Create leaders for the teams
    Cowboy *cowboyLeader = new Cowboy("CowboyLeader", Point(0, 0));
    Ninja *ninjaLeader = new OldNinja("NinjaLeader", Point(0, 0));

    // Create teams
    ariel::Team team1(cowboyLeader);
    ariel::Team2 team2(ninjaLeader);

    // Add members to team1
    Cowboy *cowboy1 = new Cowboy("Cowboy1", Point(1, 1));
    Ninja *ninja1 = new YoungNinja("Ninja1", Point(2, 2));
    team1.add(cowboy1);
    team1.add(ninja1);

    // Add members to team2
    Cowboy *cowboy2 = new Cowboy("Cowboy2", Point(1, 1));
    Ninja *ninja2 = new TrainedNinja("Ninja2", Point(2, 2));
    team2.add(cowboy2);
    team2.add(ninja2);
    std::cout << "team 1 have: " << team1.stillAlive() << std::endl;
    std::cout << "team 2 have: " << team2.stillAlive() << std::endl;

    CHECK(team1.stillAlive() == 3); // leader + 2 members
    CHECK(team2.stillAlive() == 3); // leader + 2 members

    while (team1.stillAlive() > 0 && team2.stillAlive() > 0)
    {
        std::cout << "start attack 1 has " << team1.stillAlive() << std::endl;
        team1.attack(&team2);
        if (team2.stillAlive() > 0)
        {
            std::cout << "start attack 2 has " << team2.stillAlive() << std::endl;
            team2.attack(&team1);
        }
    }

    CHECK_FALSE(((team1.stillAlive() > 0) && (team2.stillAlive() > 0))); // At least one team should be defeated
}

TEST_CASE("Dead characters cannot perform actions and characters cannot target a dead enemy")
{
    OldNinja old{"Alice", Point{1, 1}};
    YoungNinja young{"Bob", Point{2, 2}};
    Cowboy cowboy{"Charlie", Point{3, 3}};
    TrainedNinja trained("Dave", Point{4, 4});
    OldNinja old2{"Eve", Point{5, 5}};
    YoungNinja young2{"Frank", Point{6, 6}};
    Cowboy cowboy2{"Grace", Point{7, 7}};
    TrainedNinja trained2("Heidi", Point{8, 8});

    // Kill all
    while (old2.isAlive())
    {
        trained.slash(&old2);
        trained.move(&old2);
    }

    while (young2.isAlive())
    {
        trained.slash(&young2);
        trained.move(&young2);
    }

    while (trained2.isAlive())
    {
        trained.slash(&trained2);
        trained.move(&trained2);
    }

    while (cowboy2.isAlive())
    {
        trained.slash(&cowboy2);
        trained.move(&cowboy2);
    }

    // attack a dead character
    CHECK_THROWS_AS(old.slash(&young2), std::runtime_error);
    CHECK_THROWS_AS(young.slash(&trained2), std::runtime_error);
    CHECK_THROWS_AS(cowboy.shoot(&cowboy2), std::runtime_error);
    CHECK_THROWS_AS(trained.slash(&old2), std::runtime_error);

    // use a dead character to attack
    CHECK_THROWS_AS(old2.slash(&old), std::runtime_error);
    CHECK_THROWS_AS(young2.slash(&young), std::runtime_error);
    CHECK_THROWS_AS(cowboy2.shoot(&cowboy), std::runtime_error);
    CHECK_THROWS_AS(trained2.slash(&trained), std::runtime_error);
}
