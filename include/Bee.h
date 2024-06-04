#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "FoodSource.h"
#include "mavlink/common/mavlink.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>

class Bee {
protected:
    std::string id;
    POINT dancefloor;
    double radius;
    std::vector<std::shared_ptr<FoodSource>> newSources;
    POINT currentPosition;
 

public:
   sockaddr_in addr;
    int sock;

    Bee();
    Bee(const std::string& id, const POINT& dancefloor, double radius);
    virtual ~Bee();

    void moveToPoint(int sock, const sockaddr_in& addr, const POINT& point);
    void doWaggleDance(const std::shared_ptr<FoodSource> source);
    bool scanNectar();
    std::vector<POINT>& localSearch(std::shared_ptr<FoodSource> source, double radius);
    virtual void processBee() = 0;
    void addSourceToTempMemory(std::shared_ptr<FoodSource> source);

    int create_socket();
    void connect_socket(int sock, const sockaddr_in &addr);
    void close_socket(int sock);

    bool receive_mavlink_message(int sock, mavlink_message_t& msg);
    void send_mavlink_message(int sock, mavlink_message_t& msg, const sockaddr_in& addr);

    bool is_drone_ready_to_arm(int sock);
    bool are_motors_armed(int sock);
    bool is_mode_guided(int sock);
    bool is_altitude_reached(int sock, float target_altitude);
    bool is_waypoint_reached(int sock, const POINT& point, float threshold = 0.00001);

    void arm_drone(int sock, const sockaddr_in &addr, bool arm);
    void set_mode_guided(int sock, const sockaddr_in& addr);
    void send_waypoint(int sock, const sockaddr_in& addr, const POINT& point);
    void takeoff(int sock, const sockaddr_in &addr, float altitude);
};
