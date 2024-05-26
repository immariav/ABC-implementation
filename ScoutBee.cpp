#include "ScoutBee.h"
#include <corecrt_math.h>
#include <cmath>
#include <random>

ScoutBee::ScoutBee() : Bee()
{
	this->searchArea.first = { 0, 0 };
	this->searchArea.second = { 0, 0 };
	this->knownSources = {};
}

ScoutBee::ScoutBee(const std::string id, POINT& dancefloor, double radius, std::pair<POINT, POINT>& searchArea) 
	: Bee(id, dancefloor, radius)
{
	this->searchArea = searchArea;
	this->knownSources = {};
	this->newSources = {};
}

ScoutBee::~ScoutBee()
{
}

double ScoutBee::distance(const POINT& p1, const POINT& p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool ScoutBee::isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance)
{
	for (const auto& source : sources) {
		if (distance(newPoint, source->getLocation()) < minDistance) {
			return false; // точка слишком близко к другой точке
		}
	}
	return true; // точка находитс€ на достаточном рассто€нии от всех точек
}

FoodSource ScoutBee::generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distX(searchArea.first.x, searchArea.second.x); // границы значений дл€ генерации,
	std::uniform_real_distribution<double> distY(searchArea.second.y, searchArea.first.y); // чтобы точка лежала внутри пространства поиска

	POINT newPoint;
	do
	{
		newPoint = { distX(gen), distY(gen) };

	} while (!isValidPoint(newPoint, this->knownSources, minDistance));

	FoodSource newSource(newPoint); // создание экземпл€ра класса источника

	return newSource;
}

void ScoutBee::processBee()
{
	std::shared_ptr<FoodSource> newSource;
	bool nectarFound = false; // пока что разведчиком не найден нектар
	do
	{
		newSource = std::make_shared<FoodSource>(this->generateNewFoodSource(this->searchArea, this->radius)); // генераци€ нового источника
		this->moveToPoint(newSource->getLocation()); // разведчик к нему отправл€етс€
		nectarFound = this->scanNectar();
		if (!nectarFound) // если на этой точке не найден нектар, то мы ее осматриваем в большем радиусе
		{
			auto check = this->localSearch(newSource, this->radius);
			if (check.size())
			{
				for (uint32_t i = 0; i < check.size(); i++)
				{
					this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
					this->knownSources.push_back(newSources[i]);
				}
					
				nectarFound = true;
			}
			else newSource->markAsAbandoned(); // если в радиусе ничего не найдено, то забрасываем
		}
	} while (!nectarFound); // повтор€ем генерацию, пока разведчик не найдет источник с нектаром
	this->moveToPoint(this->dancefloor); // отправл€емс€ на танцпол
	for(uint32_t i = 0; i < this->newSources.size(); i++)
		this->doWaggleDance(this->newSources[i]); // исполн€ем танец дл€ передачи информации
	this->newSources = {};
}

