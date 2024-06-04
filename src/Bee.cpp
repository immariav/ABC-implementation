#include "Bee.h"

Bee::Bee()
    : id(""), dancefloor{0, 0}, radius(0), currentPosition{0, 0} {

    std::cout << "started creating socket" << std::endl;
    sock = create_socket();
    std::cout << "socket created" << std::endl;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(14550); // Порт дрона udp14550 tcp5760 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес дрона

    connect_socket(sock, addr);
    std::cout << "socket connected" << std::endl;

    while(!is_drone_ready_to_arm(sock)){
        sleep(1);
    }

    arm_drone(sock, addr, true); // only then arm
    sleep(2);

    set_mode_guided(sock, addr);
    std::cout << "GUIDED set." << std::endl;
    
    // waiting for GUIDED mode
    while (!is_mode_guided(sock)) {
        sleep(1);
    }

    std::cout << "Prepare to takeoff." << std::endl;

    takeoff(sock, addr, 2); // ending when needed altitude is reached
    if (is_altitude_reached(sock, 2)) { 
        std::cout << "Target altitude reached." << std::endl;
    } else {
        std::cerr << "Failed to reach target altitude." << std::endl;
    }

    std::cout << "drone " << id << " has ended its preparations." << std::endl;

}

Bee::Bee(const std::string& id, const POINT& dancefloor, double radius)
    : id(id), dancefloor(dancefloor), radius(radius), currentPosition{0, 0}
{
    std::cout << "started creating socket" << std::endl;
    sock = create_socket();
    std::cout << "socket created" << std::endl;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(14550); // Порт дрона udp14550 tcp5760 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес дрона

    connect_socket(sock, addr);
    std::cout << "socket connected" << std::endl;

    if(is_drone_ready_to_arm(sock))
        std::cout << "Drone is ready for arming." << std::endl;
    else 
        std::cerr << "Drone is not ready for arming." << std::endl;

    set_mode_guided(sock, addr);
    std::cout << "GUIDED command sent." << std::endl;

    // waiting for GUIDED mode
    if(is_mode_guided(sock))
        std::cout << "GUIDED mode is set." << std::endl;
    else 
        std::cerr << "GUIDED mode is not set." << std::endl;

    arm_drone(sock, addr, true); // only then arm
    
    if(are_motors_armed(sock))
        std::cout << "Motors are armed and running." << std::endl;
    else 
        std::cerr << "Motors are not armed." << std::endl;

    std::cout << "Prepare to takeoff." << std::endl;

    takeoff(sock, addr, 2); // ending when needed altitude is reached
    if (is_altitude_reached(sock, 2)) { 
        std::cout << "Target altitude reached." << std::endl;
    } else {
        std::cerr << "Failed to reach target altitude." << std::endl;
    }

    std::cout << "drone " << id << " has ended its preparations." << std::endl;
}

Bee::~Bee() {
    close_socket(sock);
}

void Bee::moveToPoint(int sock, const sockaddr_in& addr, const POINT& point)
{
	send_waypoint(sock, addr, point);
    if (is_waypoint_reached(sock, point)) { 
        std::cout << "Target point reached." << std::endl;
    } else {
        std::cerr << "Failed to reach target point." << std::endl;
    }
}

void Bee::doWaggleDance(const std::shared_ptr<FoodSource> source)
{
	
}

bool Bee::scanNectar()
{
	
	return false; 
}

std::vector<POINT>& Bee::localSearch(std::shared_ptr<FoodSource> source, double radius)
{
    static std::vector<POINT> points = {}; // Placeholder, replace with actual implementation
    return points;
}

void Bee::addSourceToTempMemory(std::shared_ptr<FoodSource> source)
{
	this->newSources.push_back(source);
}

int Bee::create_socket()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sock;
}

void Bee::connect_socket(int sock, const sockaddr_in &addr) {
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
}

void Bee::close_socket(int sock)
{
    close(sock);
}

bool Bee::receive_mavlink_message(int sock, mavlink_message_t &msg)
{
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    ssize_t nbytes = recv(sock, buffer, sizeof(buffer), 0);
    if (nbytes < 0) {
        perror("recv failed");
        return false;
    }

    mavlink_status_t status;
    for (ssize_t i = 0; i < nbytes; ++i) {
        if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
            return true;
        }
    }
    return false;
}

void Bee::send_mavlink_message(int sock, mavlink_message_t &msg, const sockaddr_in &addr)
{
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    ssize_t bytes_sent = sendto(sock, buffer, len, 0, (sockaddr*)&addr, sizeof(addr));
    if (bytes_sent != len) {
        std::cerr << "Failed to send MAVLink message. Bytes sent: " << bytes_sent << std::endl;
    } else {
        std::cout << "MAVLink message sent successfully." << std::endl;
    }
}

bool Bee::is_drone_ready_to_arm(int sock) {
    mavlink_message_t msg;
    mavlink_status_t status;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    ssize_t recsize;
    socklen_t fromlen;

    // Сформировать MAVLink сообщение запроса статуса дрона
    mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_GCS, MAV_AUTOPILOT_GENERIC, 0, 0, 0);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    send(sock, buf, len, 0);

    bool is_ready = false;
    while(!is_ready) {
        // Получить ответ от дрона
        recsize = recvfrom(sock, buf, MAVLINK_MAX_PACKET_LEN, 0, nullptr, nullptr);
        if (recsize > 0) {
            for (ssize_t i = 0; i < recsize; ++i) {
                if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) {
                    if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                        mavlink_heartbeat_t heartbeat;
                        mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                        // Проверка готовности к взлету (arming state)
                        if (heartbeat.system_status == MAV_STATE_STANDBY || heartbeat.system_status == MAV_STATE_ACTIVE) 
                            is_ready = true;
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return is_ready;
}

bool Bee::are_motors_armed(int sock)
{
    // Отправка запроса статуса системы через MAVLink
    mavlink_message_t msg;
    mavlink_request_data_stream_t request;
    request.target_system = 1; // ID системы дрона (в SITL обычно 1)
    request.target_component = 1; // ID компонента дрона (обычно 1 для автопилота)
    request.req_stream_id = MAV_DATA_STREAM_EXTENDED_STATUS; // Идентификатор потока данных
    request.req_message_rate = 1; // Частота запроса
    request.start_stop = 1; // Начать поток данных

    mavlink_msg_request_data_stream_encode(1, 200, &msg, &request); // Сообщение MAVLink

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    send(sock, buffer, len, 0);

    // Получение сообщения от дрона
    bool motorsArmed = false;
    while (!motorsArmed) {
        if (receive_mavlink_message(sock, msg)) {
            // Проверка сообщения на состояние моторов
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                motorsArmed = (heartbeat.base_mode & MAV_MODE_FLAG_SAFETY_ARMED) != 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return motorsArmed;
}

bool Bee::is_mode_guided(int sock)
{
    mavlink_message_t msg;
    mavlink_request_data_stream_t request;
    request.target_system = 1;
    request.target_component = 1;
    request.req_stream_id = MAV_DATA_STREAM_EXTENDED_STATUS;
    request.req_message_rate = 1;
    request.start_stop = 1;

    mavlink_msg_request_data_stream_encode(1, 200, &msg, &request);

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    send(sock, buffer, len, 0);

    std::cout << "MAVLink status request sent." << std::endl;

    bool modeGuided = false;
    int attempts = 0;
    while (!modeGuided && attempts < 50) {
        if (receive_mavlink_message(sock, msg)) {
            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);

                std::cout << "Received HEARTBEAT: base_mode=" << static_cast<int>(heartbeat.base_mode)
                          << " custom_mode=" << heartbeat.custom_mode
                          << " system_status=" << static_cast<int>(heartbeat.system_status)
                          << " mavlink_version=" << static_cast<int>(heartbeat.mavlink_version)
                          << std::endl;

                if ((heartbeat.base_mode & MAV_MODE_FLAG_GUIDED_ENABLED) && heartbeat.custom_mode == 4) {
                    modeGuided = true;
                }
            } else {
                std::cout << "Received message id: " << msg.msgid << std::endl;
            }
        } else {
            std::cout << "No MAVLink message received." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        attempts++;
    }

    if (!modeGuided) {
        std::cerr << "Failed to set GUIDED mode." << std::endl;
    }
    return modeGuided;
}
    

bool Bee::is_altitude_reached(int sock, float target_altitude)
{
    mavlink_message_t msg;
    while (true) { //don't stop until the drone is on the right altitude
        // cur altitude info
        mavlink_msg_request_data_stream_pack(1, 200, &msg, 1, 1, MAV_DATA_STREAM_POSITION, 1, 1);
        send_mavlink_message(sock, msg, addr);
        if (receive_mavlink_message(sock, msg)) {
            if (msg.msgid == MAVLINK_MSG_ID_GLOBAL_POSITION_INT) {
                mavlink_global_position_int_t position;
                mavlink_msg_global_position_int_decode(&msg, &position);
                float altitude = position.relative_alt / 1000.0; // относительная высота в метрах
                if (altitude >= target_altitude) { 
                    return true;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Bee::is_waypoint_reached(int sock, const POINT& point, float threshold) {
    mavlink_message_t msg;
    while (true) {
        // cur location
        mavlink_msg_request_data_stream_pack(1, 200, &msg, 1, 1, MAV_DATA_STREAM_POSITION, 1, 1);
        send_mavlink_message(sock, msg, addr);
        if (receive_mavlink_message(sock, msg)) {
            if (msg.msgid == MAVLINK_MSG_ID_GLOBAL_POSITION_INT) {
                mavlink_global_position_int_t position;
                mavlink_msg_global_position_int_decode(&msg, &position);
                float current_latitude = position.lat / 1E7;
                float current_longitude = position.lon / 1E7;
                if (std::abs(current_latitude - point.x) < threshold &&
                    std::abs(current_longitude - point.y) < threshold) {
                    return true;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Bee::arm_drone(int sock, const sockaddr_in& addr, bool arm) {
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(1, 200, &msg, 1, 1, MAV_CMD_COMPONENT_ARM_DISARM, 0, arm ? 1 : 0, 0, 0, 0, 0, 0, 0);
    send_mavlink_message(sock, msg, addr);
    std::cout << (arm ? "Arming" : "Disarming") << " drone!" << std::endl;
}

void Bee::set_mode_guided(int sock, const sockaddr_in &addr)
{
    mavlink_message_t msg;
    mavlink_command_long_t cmd;

    cmd.target_system = 1; // ID системы дрона (в SITL обычно 1)
    cmd.target_component = 1; // ID компонента дрона (обычно 1 для автопилота)
    cmd.command = MAV_CMD_DO_SET_MODE;
    cmd.confirmation = 0;
    cmd.param1 = MAV_MODE_FLAG_CUSTOM_MODE_ENABLED; // Флаг установки custom mode
    cmd.param2 = 4; // Установка GUIDED режима
    cmd.param3 = 0;
    cmd.param4 = 0;
    cmd.param5 = 0;
    cmd.param6 = 0;
    cmd.param7 = 0;

    mavlink_msg_command_long_encode(1, 200, &msg, &cmd);

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
    sendto(sock, buffer, len, 0, (struct sockaddr*)&addr, sizeof(addr));

    std::cout << "GUIDED mode command sent." << std::endl;
}

void Bee::takeoff(int sock, const sockaddr_in &addr, float altitude)
{
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(1, 200, &msg, 1, 1, MAV_CMD_NAV_TAKEOFF, 0, 0, 0, 0, 0, 0, 0, altitude);
    send_mavlink_message(sock, msg, addr);
    std::cout << "Takeoff command sent to altitude: " << altitude << " meters!" << std::endl;
}

void Bee::send_waypoint(int sock, const sockaddr_in& addr, const POINT& point)
{
    mavlink_message_t msg;
    mavlink_msg_command_long_pack(1, 200, &msg, 1, 1, MAV_CMD_NAV_WAYPOINT, 0, 0, 0, 0, 0, point.x, point.y, 0);
    send_mavlink_message(sock, msg, addr);
    std::cout << "Waypoint command sent to (" << point.x << ", " << point.y << ", " << 0 << ")!" << std::endl;
}
