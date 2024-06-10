#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <thread>

class DroneLauncher {
public:
    DroneLauncher(int id) : drone_id(id) {}

    void launch();
private:
    int drone_id;

    void create_named_pipe();
    void start_sitl_instance();
};

// int main() {
//     std::cout << "Enter the number of drones: ";
//     int num_drones;
//     std::cin >> num_drones;

//     std::vector<std::thread> threads;
//     for (int i = 0; i < num_drones; ++i) {
//         DroneLauncher launcher(i);
//         threads.emplace_back(&DroneLauncher::launch, launcher);
//     }

//     for (auto &thread : threads) {
//         thread.join();
//     }

//     return 0;
// }
