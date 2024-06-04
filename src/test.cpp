#include <iostream>
#include "Hive.h"

int main()
{
     std::cout << "Running program" << std::endl;
    EmployedBee bee(std::to_string(1), 
    {-35.36043975, 149.15909315}, 
    10.0, 
    {-35.36043975, 149.15909315}, 
    {{-35.36043975, 149.15909315}, {-35.36337074, 149.16383840}});
    
    bee.moveToPoint(bee.sock, bee.addr, {-35.36043975, 149.15909315});
}
