#include "DroneLauncher.h"


void DroneLauncher::launch() {
    create_named_pipe();
    start_sitl_instance();
}


void DroneLauncher::create_named_pipe() {
    std::string pipe_name = "/tmp/drone_pipe_" + std::to_string(drone_id);
    mkfifo(pipe_name.c_str(), 0666);
    std::ofstream pipe(pipe_name);
    if (pipe.is_open()) {
        pipe << drone_id;
        pipe.close();
    } else {
        std::cerr << "Failed to open named pipe for drone " << drone_id << std::endl;
    }
    }

void DroneLauncher::start_sitl_instance() {
    std::string command = "sim_vehicle.py -v ArduCopter -f gazebo-iris --console -I" + std::to_string(drone_id) +
                            " --out=udp:127.0.0.1:" + std::to_string(14550 + drone_id) + " --custom-build --parm-file=~/path/to/drone" + std::to_string(drone_id + 1) + ".parm";
    std::system(command.c_str());
}


int main() {
    std::cout << "Enter the number of drones: ";
    int num_drones;
    std::cin >> num_drones;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_drones; ++i) {
        DroneLauncher launcher(i);
        threads.emplace_back(&DroneLauncher::launch, launcher);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return 0;
}
