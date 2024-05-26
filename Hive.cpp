#include "Hive.h"
#include <corecrt_math.h>
#include <cmath>
#include <random>

Hive::Hive() 
{
	this->swarmSize = 0;
	this->scoutsQty = 0;
	this->onlookersQty = 0;
	this->employeesQty = 0;
	this->currentNectarAmount = 0;
	this->goal = 0;
	this->minDistBetweenSources = 0;
	this->destinationPoint = { 0, 0 };
	this->searchArea.first = { 0, 0 };
	this->searchArea.second = { 0, 0 };
	this->destinationPoint = { 0, 0 };
	this->dancefloor = { 0, 0 };
}

Hive::~Hive()
{}

Hive::Hive(uint32_t swarmSize, uint32_t goal)
{
	setSwarmSize(swarmSize);
	setGoal(goal);
}

void Hive::setSwarmSize(uint32_t size)
{
	if (size >= 3)
	{
		this->swarmSize = size;
		this->scoutsQty = 1;
		this->onlookersQty = static_cast<uint32_t>(trunc(swarmSize / 2));
		this->employeesQty = swarmSize - this->scoutsQty - this->onlookersQty;
		this->scouts.reserve(scoutsQty);
		this->onlookers.reserve(onlookersQty);
		this->employees.reserve(employeesQty);
	}
	else
	{}
}

void Hive::setGoal(uint32_t goal)
{
	if (goal > 0)
		this->goal = goal;
}

void Hive::setDestinationPoint(double x, double y)
{
	if(isPointOutsideSA({ x, y }, this->getSearchAreaTopLeft(), this->getSearchAreaBottomRight()))
		this->destinationPoint = { x, y };
}

uint32_t Hive::getGoal() const
{
	return this->goal;
}

double Hive::getSearchAreaWidth() const
{
	return this->searchArea.second.x - this->searchArea.first.x;
}

double Hive::getSearchAreaHeight() const
{
	return this->searchArea.first.y - this->searchArea.second.y;
}

double Hive::getMinDistBetweenSources() const
{
	return std::min(getSearchAreaWidth(), getSearchAreaHeight());
}

POINT Hive::getSearchAreaTopLeft() const
{
	return this->searchArea.first;
}

POINT Hive::getSearchAreaBottomRight() const
{
	return this->searchArea.second;
}

POINT Hive::getDancefloorPoint() const
{
	return this->dancefloor;
}

void Hive::increaseCurrentNectarAmoiunt()
{
	this->currentNectarAmount++;
}

void Hive::initializeDrones(const std::vector<std::string>& droneIds)
{
	if (this->swarmSize) // проверка на то, что размер роя уже был задан
	{
		for (uint32_t i = 0; i < this->employeesQty; ++i) {
			this->employees.emplace_back(std::make_unique<EmployedBee>(droneIds[i], this->dancefloor, 
				this->getMinDistBetweenSources(), this->destinationPoint));
		}

		for (uint32_t i = this->employeesQty; i < this->employeesQty + this->scoutsQty; ++i) {
			this->scouts.emplace_back(std::make_unique<ScoutBee>(droneIds[i], this->dancefloor, 
			 this->getMinDistBetweenSources(), this->searchArea));
		}

		for (uint32_t i = this->employeesQty + this->scoutsQty; i < this->employeesQty + this->scoutsQty + this->onlookersQty; ++i) {
			this->onlookers.emplace_back(std::make_unique<OnlookerBee>(droneIds[i], this->dancefloor, 
				 this->getMinDistBetweenSources()));
		}
	}
}

bool Hive::isValidSearchArea(double xTopLeft, double yTopLeft, double xBottomRight, double yBottomRight)
{
	// левый x должен быть меньше правого, иначе прямоугольник пустой или некорректно задан. аналогично верхний y должен быть больше нижнего
	if (xTopLeft >= xBottomRight || yTopLeft <= yBottomRight) {
		return false; // некорректные координаты
	}
	return true; // проверки пройдены успешно
}

bool Hive::isPointOutsideSA(const POINT& point, const POINT& topLeft, const POINT& bottomRight)
{
	// проверяем, что точка не лежит внутри прямоугольника
	return point.x < topLeft.x || point.x > bottomRight.x || point.y > topLeft.y || point.y < bottomRight.y;
}

// сначала x, y левой верхней точки; потом x, y правой нижней точки
void Hive::setSearchArea(double xTopLeft, double yTopLeft, double xBottomRight, double yBottomRight)
{
	if (isValidSearchArea(xTopLeft, yTopLeft, xBottomRight, yBottomRight))
	{
		this->searchArea.first.x = xTopLeft;
		this->searchArea.first.y = yTopLeft;
		this->searchArea.second.x = xBottomRight;
		this->searchArea.second.y = yBottomRight;
	}
	else {}
}

// сначала левая верхняя точка; потом правая нижняя точка
void Hive::setSearchArea(const POINT& topLeft, const POINT& bottomRight)
{
	if(isValidSearchArea(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y))
	{
		this->searchArea.first = topLeft;
		this->searchArea.second = bottomRight;
	}
	else {}
}

void Hive::Solve()
{
	do {
		
		for(auto& scout : this->scouts) // фаза разведчиков
			scout->processBee();
		
		for (auto& employee : this->employees) // фаза рабочих
			employee->processBee();
		
		for (auto& onlooker : this->onlookers) // фаза наблюдателей
			onlooker->processBee();

	} while (this->currentNectarAmount < this->goal); // проверка достижения цели
}

