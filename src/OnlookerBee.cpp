#include <iostream>
#include <vector>
#include <cstdlib> 
#include <random>
#include <vector>
#include <memory>
#include "OnlookerBee.h"

std::vector<POINT> OnlookerBee::spiral_points(const POINT &center, const double step)
{
    std::vector<POINT> points;
    const double a = radius;
    const double b = step / (2 * M_PI); // коэффициент для управления шагом спирали

    double theta = 0.0;
    double r = a;

    while (r <= onlookerSearchCoef * radius) {
        double x = center.x + r * cos(theta);
        double y = center.y + r * sin(theta);
        points.push_back({x, y});

        theta += step / r; // увеличиваем угол
        r = a * exp(b * theta); // увеличиваем радиус
    }

    return points;
}

OnlookerBee::OnlookerBee(const int id) : Bee(id) {}

OnlookerBee::~OnlookerBee() {}

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

