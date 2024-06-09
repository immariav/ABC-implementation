#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "FoodSource.h"
#include "DroneController.h"

#define onlookerSearchCoef = 1.5

class Bee {
protected:
    int id;
    
    double radius = 7.5;
    std::pair<POINT, POINT> searchArea = {{-35.36043975, 149.15909315}, // top left
                                        {-35.36337074, 149.16383840} // bottom right
    };

    POINT destination = {-35.36043970, 149.15909315}; // should not be inside the search area

    std::shared_ptr<FoodSource> currentSource; // current working source and current dancefloor
    std::vector<std::shared_ptr<FoodSource>> sourcesToShare; // sources that bees find during local search
    std::vector<std::shared_ptr<FoodSource>> recievedSources; // sources that bees recieve from waggle dances
    std::vector<std::shared_ptr<FoodSource>> sourcesToCheck;

    std::vector<POINT> spiral_points(const POINT& center, const double step = 0.5) ;

    virtual std::vector<POINT>& localSearch(const POINT& location, double radius) = 0;

    void moveToPoint(const POINT& point);
    void doWaggleDance(std::vector<std::shared_ptr<FoodSource>> sourcesToShare);
    void watchWaggleDance();
    bool scanNectar();

public:
    Bee(const int id);
    virtual ~Bee();

    virtual void processBee() = 0;
};
