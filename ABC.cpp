#include <iostream>
#include "Hive.h"

int main()
{
    Hive hive;
    hive.setSwarmSize(50);
    hive.setGoal(900);
    hive.setSearchArea({1000, 0}, {0, 500});
    hive.setDestinationPoint(-50, -50);

    hive.Solve();
}
