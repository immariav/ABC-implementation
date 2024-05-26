#pragma once
#include "Bee.h"
class EmployedBee :
    public Bee
{
private:

    std::pair<POINT, POINT> searchArea;

    std::shared_ptr<FoodSource> currentSource;
    POINT destination; // точка сбора материала

    //пчела несет нектар на точку
    void carryNectar(std::shared_ptr<FoodSource> source, const POINT& point); // (откуда, куда)
    std::shared_ptr<FoodSource> getCurrentSource();

    //вычисление Евклидова расстояния между двумя точками
    double distance(const POINT& p1, const POINT& p2); //вычисление Евклидова расстояния между двумя точками
    // проверка на то, что точка не соответствует уже существующим и вписывается в параметры минимального расстояния
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);
    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

public:

    using Bee::Bee;
    EmployedBee();
    EmployedBee(const std::string id, POINT& dancefloor, double radius, POINT& destination, std::pair<POINT, POINT>& searchArea);
    ~EmployedBee();
    // функция обработки рабочего
    void processBee() override;
};

