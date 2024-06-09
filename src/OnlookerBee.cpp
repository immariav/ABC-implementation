#include <iostream>
#include <vector>
#include <cstdlib> 
#include <random>
#include <vector>
#include <memory>
#include "OnlookerBee.h"

OnlookerBee::OnlookerBee(const int id) : Bee(id){}

OnlookerBee::~OnlookerBee() {}

std::vector<POINT>& Bee::localSearch(const POINT&, double radius)
{
    static std::vector<POINT> points = {}; // Placeholder, replace with actual implementation
	// move to the this->currentSource->getLocation();
    return points;
}

void OnlookerBee::processBee()
{
    std::cout << "Onlooker Bee id " << this->id << " started working" << std::endl;
    
    watchWaggleDance(); // maybe lighting up

	while (!sourcesToCheck.empty())
	{
        currentSource = sourcesToCheck.front();

        moveToPoint(currentSource->getLocation());

        localSearch(currentSource->getLocation(), radius);

        moveToPoint(currentSource->getLocation());

        doWaggleDance(sourcesToShare);

        watchWaggleDance();
	}

    std::cout << "Onlooker Bee id " << this->id << " returned to the dancefloor" << std::endl;
}

