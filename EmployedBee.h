#pragma once
#include "Bee.h"
class EmployedBee :
    public Bee
{
private:

    std::shared_ptr<FoodSource> currentSource;
    POINT destination; // точка сбора материала

    //пчела несет нектар на точку
    void carryNectar(std::shared_ptr<FoodSource> source, const POINT& point); // (откуда, куда)
    std::shared_ptr<FoodSource> getCurrentSource();

public:

    using Bee::Bee;
    EmployedBee();
    EmployedBee(const std::string id, POINT& dancefloor, double radius, POINT& destination);
    ~EmployedBee();
    // функция обработки рабочего
    void processBee() override;
};

