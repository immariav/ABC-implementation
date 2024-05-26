#pragma once
#include <cstdint>
#include <string>
#include <set>
#include "EmployedBee.h"
#include "ScoutBee.h"
#include "OnlookerBee.h"
#include <utility>
#include <memory>

class Hive
{
private:

	uint32_t swarmSize; // размер роя
	uint32_t onlookersQty; // количество наблюдателей
	uint32_t scoutsQty; // количество разведчиков
	uint32_t employeesQty; // количество рабочих

	std::vector<std::unique_ptr<OnlookerBee>> onlookers; // массив указателей на наблюдателей 
	std::vector<std::unique_ptr<ScoutBee>> scouts; // массив указателей на разведчиков 
	std::vector<std::unique_ptr<EmployedBee>> employees; // массив указателей на рабочих 

	uint32_t currentNectarAmount; // текущее количество нектара
	uint32_t goal; // целевая функция

	double minDistBetweenSources; // минимальное возможное расстояние между источниками

	POINT destinationPoint; // точка сбора материала
	POINT dancefloor; // координаты танцпола

	std::pair<POINT, POINT> searchArea; // полигон (пространство поиска)

	// проверка введенных координат полигона на корректность
	bool isValidSearchArea(double xTopLeft, double yTopLeft, double xBottomRight, double yBottomRight); 

	// точка сбора должна быть за пространством поиска
	bool isPointOutsideSA(const POINT& point, const POINT& topLeft, const POINT& bottomRight);

public:

	Hive();
	Hive(uint32_t swarmSize, uint32_t goal);
	~Hive();

	void setSwarmSize(uint32_t size);
	void setGoal(uint32_t goal);
	void setDestinationPoint(double x, double y);
	void setSearchArea(const POINT& topLeft, const POINT& bottomRight);
	void setSearchArea(double xTopLeft, double yToppLeft, double xBottomRight, double yBottomRight);

	uint32_t getGoal() const;
	POINT getSearchAreaTopLeft() const;
	POINT getSearchAreaBottomRight() const;
	double getSearchAreaWidth() const;
	double getSearchAreaHeight() const;
	double getMinDistBetweenSources() const;
	POINT getDancefloorPoint() const;
	std::set<FoodSource> getKnownSources() const;
	// функция, которая извне увеличивает текущее число нектара
	void increaseCurrentNectarAmoiunt();

	// сопоставление дронов объектам програмнного кода
	void initializeDrones(const std::vector<std::string>& droneIds); 

	// основная логика алгоритма
	void Solve(); 
};

