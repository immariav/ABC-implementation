#pragma once
#include "Bee.h"
class ScoutBee :
    public Bee
{
private:

    std::pair<POINT, POINT> searchArea;
    std::vector<std::shared_ptr<FoodSource>> knownSources;


    //вычисление Евклидова расстояния между двумя точками
    double distance(const POINT& p1, const POINT& p2); //вычисление Евклидова расстояния между двумя точками
    // проверка на то, что точка не соответствует уже существующим и вписывается в параметры минимального расстояния
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);

    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

public:

    using Bee::Bee;
    ScoutBee();
    ScoutBee(const std::string id, POINT& dancefloor, double radius, std::pair<POINT, POINT>& searchArea);
    ~ScoutBee();
    // функция обработки разведчика
    void processBee() override;
};

