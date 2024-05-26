#pragma once
#include "Bee.h"
class OnlookerBee :
    public Bee
{
private:
    std::shared_ptr<FoodSource> chosenSource;

    void chooseFoodSource();
    void addSourceToMemory(std::shared_ptr<FoodSource> source); // ��������� �������� � ������ �����
    std::shared_ptr<FoodSource> getChosenSource();

public:

    using Bee::Bee;
    OnlookerBee();
    OnlookerBee(const std::string id, POINT& dancefloor, double radius, POINT& destination);
    ~OnlookerBee();
    // ������� ��������� �����������
    void processBee() override;
};

