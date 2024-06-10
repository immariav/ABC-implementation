#pragma once
#include "Bee.h"
class OnlookerBee : public Bee
{
private:
   // fields
   std::vector<POINT> spiral_points(const POINT& center, const double step = 0.5) override;

public:

    using Bee::Bee;
    OnlookerBee(const int id);
    ~OnlookerBee() override;
    
    void processBee() override;
};

