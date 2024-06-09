#pragma once
#include "Bee.h"
class OnlookerBee : public Bee
{
private:
   // fields

    virtual std::vector<POINT>& localSearch(const POINT&, double radius);

public:

    using Bee::Bee;
    OnlookerBee(const int id);
    ~OnlookerBee() override;
    

    void processBee() override;
};

