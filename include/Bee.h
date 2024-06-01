#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "FoodSource.h"

class Bee {
protected:
    std::string id;
    POINT dancefloor;
    double radius;
    std::vector<std::shared_ptr<FoodSource>> newSources;
    POINT currentPosition;

public:
    Bee();
    Bee(const std::string& id, POINT& dancefloor, double radius);
    virtual ~Bee();

    void moveToPoint(const POINT& point);
    void doWaggleDance(const std::shared_ptr<FoodSource> source);
    bool scanNectar();
    std::vector<POINT>& localSearch(std::shared_ptr<FoodSource> source, double radius);
    virtual void processBee() = 0;
    void addSourceToTempMemory(std::shared_ptr<FoodSource> source);
};
