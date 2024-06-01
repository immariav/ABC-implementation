#pragma once
#include "../include/Bee.h"

Bee::Bee()
    : id(""), dancefloor{0, 0}, radius(0), currentPosition{0, 0} {}

Bee::Bee(const std::string& id, POINT& dancefloor, double radius)
    : id(id), dancefloor(dancefloor), radius(radius), currentPosition{0, 0}{}

Bee::~Bee() {}

void Bee::moveToPoint(const POINT& point)
{
	this->currentPosition = point;
}

void Bee::doWaggleDance(const std::shared_ptr<FoodSource> source)
{
	
}

bool Bee::scanNectar()
{
	
	return false; 
}

std::vector<POINT>& Bee::localSearch(std::shared_ptr<FoodSource> source, double radius)
{
    static std::vector<POINT> points = {}; // Placeholder, replace with actual implementation
    return points;
}

void Bee::addSourceToTempMemory(std::shared_ptr<FoodSource> source)
{
	this->newSources.push_back(source);
}

