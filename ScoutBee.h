#pragma once
#include "Bee.h"
class ScoutBee :
    public Bee
{
private:

    std::pair<POINT, POINT> searchArea;
    std::vector<std::shared_ptr<FoodSource>> knownSources;


    //вычисление ≈вклидова рассто€ни€ между двум€ точками
    double distance(const POINT& p1, const POINT& p2); //вычисление ≈вклидова рассто€ни€ между двум€ точками
    // проверка на то, что точка не соответствует уже существующим и вписываетс€ в параметры минимального рассто€ни€
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);

    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

    //добавл€ем источник в пам€ть разведчика
    void addSourceToMemory(std::shared_ptr<FoodSource> newSource);
    // std::vector<FoodSource> getKnownSources();

public:

    using Bee::Bee;
    ScoutBee();
    ScoutBee(const std::string id, POINT& dancefloor, double radius, std::pair<POINT, POINT>& searchArea);
    ~ScoutBee();
    // функци€ обработки разведчика
    void processBee() override;
};

