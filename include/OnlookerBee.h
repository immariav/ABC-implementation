#pragma once
#include "Bee.h"
class OnlookerBee : public Bee
{
private:
    std::shared_ptr<FoodSource> chosenSource;
    std::vector<std::shared_ptr<FoodSource>> activeSources; // ���������, ���������� � ������� ����������� �������� �� ������ ����� ������

    void chooseFoodSource();
    std::shared_ptr<FoodSource> getChosenSource();

public:

    using Bee::Bee;
    OnlookerBee();
    OnlookerBee(const std::string& id, POINT& dancefloor, double radius);
    ~OnlookerBee() override;
    // ������� ��������� �����������
    void processBee() override;
};

