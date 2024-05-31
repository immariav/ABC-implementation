#pragma once
#include "Bee.h"
class OnlookerBee :
    public Bee
{
private:
    std::shared_ptr<FoodSource> chosenSource;
    std::vector<std::shared_ptr<FoodSource>> activeSources; // источники, информацию о которых наблюдатель получает на первом этапе выбора

    void chooseFoodSource();
    std::shared_ptr<FoodSource> getChosenSource();

public:

    using Bee::Bee;
    OnlookerBee();
    OnlookerBee(const std::string id, POINT& dancefloor, double radius, POINT& destination);
    ~OnlookerBee();
    // функция обработки наблюдателя
    void processBee() override;
};

