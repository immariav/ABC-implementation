#pragma once
#include "Bee.h"
class ScoutBee :
    public Bee
{
private:

    std::pair<POINT, POINT> searchArea;
    std::vector<std::shared_ptr<FoodSource>> knownSources;


    //���������� ��������� ���������� ����� ����� �������
    double distance(const POINT& p1, const POINT& p2); //���������� ��������� ���������� ����� ����� �������
    // �������� �� ��, ��� ����� �� ������������� ��� ������������ � ����������� � ��������� ������������ ����������
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);

    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

    //��������� �������� � ������ ����������
    void addSourceToMemory(std::shared_ptr<FoodSource> newSource);
    // std::vector<FoodSource> getKnownSources();

public:

    using Bee::Bee;
    ScoutBee();
    ScoutBee(const std::string id, POINT& dancefloor, double radius, std::pair<POINT, POINT>& searchArea);
    ~ScoutBee();
    // ������� ��������� ����������
    void processBee() override;
};

