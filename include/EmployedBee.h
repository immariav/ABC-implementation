#pragma once
#include "Bee.h"
class EmployedBee : public Bee
{
private:

    std::pair<POINT, POINT> searchArea;
    std::vector<std::shared_ptr<FoodSource>> knownSources; // ��� ��������� ����� ���������
    std::shared_ptr<FoodSource> currentSource;
    POINT destination; // ����� ����� ���������

    //����� ����� ������ �� �����
    void carryNectar(std::shared_ptr<FoodSource> source, const POINT point); // (������, ����)
    std::shared_ptr<FoodSource> getCurrentSource();

    //���������� ��������� ���������� ����� ����� �������
    double distance(const POINT& p1, const POINT& p2); //���������� ��������� ���������� ����� ����� �������
    // �������� �� ��, ��� ����� �� ������������� ��� ������������ � ����������� � ��������� ������������ ����������
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);
    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

public:

    using Bee::Bee;
    EmployedBee();
    EmployedBee(const std::string& id, const POINT& dancefloor, double radius, const POINT& destination, const std::pair<POINT, POINT>& searchArea);
    ~EmployedBee() override;
    //���������� � knownSources
    void addSourceToConstMemory(std::shared_ptr<FoodSource> source);
    // ������� ��������� ��������
    void processBee() override;
};

