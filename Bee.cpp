#include "Bee.h"

Bee::Bee()
{
	this->id = "";
	this->dancefloor = { 0, 0 };
	this->radius = 0;
	this->newSources = {};
	this->knownSources = {};
}

Bee::Bee(const std::string id, POINT& dancefloor, double radius)
{
	this->id = id;
	this->dancefloor = dancefloor;
	this->radius = radius;
	this->newSources = {};
	this->knownSources = {};
}

Bee::~Bee()
{
}

void Bee::moveToPoint(const POINT& point)
{
	// передвижение в point
}

void Bee::doWaggleDance(const std::shared_ptr<FoodSource> source)
{
	// передача знаний об источнике между пчелами
	// новый источник заносится в память пчеле с помощью соответствующего метода
}

bool Bee::scanNectar()
{
	// распознавание нектара
	return true; // пока что всегда возвращается true, чтобы комплитяор не ругался
}

std::vector<POINT>& Bee::localSearch(std::shared_ptr<FoodSource> source, double radius)
{
	double x = 0; double y = 0;
	bool nectarFound = false;
	std::vector<POINT> sourceLocations;
	// поиск в пределах radius от точки source->getLocation(). нужно облететь всю территорию
	// если найден нектар, то добавляем координаты в вектор
	if (nectarFound)
	{
		sourceLocations.push_back({ x , y });
	}
	return sourceLocations;
}

void Bee::processBee()
{
}

void Bee::addSourceToTempMemory(std::shared_ptr<FoodSource> source)
{
	this->newSources.push_back(source);
}

void Bee::addSourceToConstMemory(std::shared_ptr<FoodSource> source)
{
	this->knownSources.push_back(source);
}

