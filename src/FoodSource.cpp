#include "FoodSource.h"

FoodSource::FoodSource()
{
	this->isAbandoned = false;
	this->location.x = 0;
	this->location.y = 0;
}

FoodSource::FoodSource(const POINT& point)
{
	this->isAbandoned = false;
	this->location = point;
}

FoodSource::~FoodSource()
{
}

void FoodSource::markAsAbandoned()
{
	this->isAbandoned = true;
}

const POINT& FoodSource::getLocation() const
{
	return this->location;
}

bool FoodSource::getAbandonedStatus()
{
	return this->isAbandoned;
}
