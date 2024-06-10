#include <iostream>
#include "OnlookerBee.h"
#include "EmployedBee.h"

int main()
{
     std::cout << "Running program" << std::endl;
    EmployedBee bee(1);
    
    bee.moveToPoint({-35.36043975, 149.15909315});
}
