#pragma once
#include "Bee.h"
class EmployedBee : public Bee
{
private:

    std::pair<POINT, POINT> searchArea;
    std::vector<std::shared_ptr<FoodSource>> knownSources; // all known sources
    POINT destination; 

    //take nectar and move to the destination
    void carryNectar(std::shared_ptr<FoodSource> source, const POINT point);
    bool checkNectar(); 

    // calc distance between two points
    double distance(const POINT& p1, const POINT& p2); 
    // check if a point is not too close tp the known ones
    bool isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance);
    FoodSource generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance);

    virtual std::vector<POINT>& localSearch(const POINT&, double radius);

public:

    using Bee::Bee;
    EmployedBee(const int id);
    ~EmployedBee() override;
    //add to knownSources
   // void addSourceToConstMemory(std::shared_ptr<FoodSource> source);
   // std::shared_ptr<FoodSource> getCurrentSource();
    // ������� ��������� ��������
    void processBee() override;
};

