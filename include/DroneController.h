// C++ - Python API
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "Shapes.h"

inline void create_named_pipes(int id) {

    std::string pipe_to_python = "/tmp/drone_pipe_to_python_" + std::to_string(id);
    std::string pipe_from_python = "/tmp/drone_pipe_from_python_" + std::to_string(id);
    mkfifo(pipe_to_python.c_str(), 0666);
    mkfifo(pipe_from_python.c_str(), 0666);
}

inline void close_named_pipes(int id) {

    std::string pipe_to_python = "/tmp/drone_pipe_to_python_" + std::to_string(id);
    std::string pipe_from_python = "/tmp/drone_pipe_from_python_" + std::to_string(id);
    
    // Открываем каналы для закрытия
    int fd_to_python = open(pipe_to_python.c_str(), O_WRONLY);
    int fd_from_python = open(pipe_from_python.c_str(), O_RDONLY);

    // Закрываем каналы
    if (fd_to_python != -1)
        close(fd_to_python);
    if (fd_from_python != -1)
        close(fd_from_python);
}

inline std::vector<int> receive_vector_from_python(int id) {

    std::string pipe_from_python = "/tmp/drone_pipe_from_python_" + std::to_string(id);
    int fd = open(pipe_from_python.c_str(), O_RDONLY);

    std::ifstream ifs(pipe_from_python, std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);
    std::vector<int> received_vector;
    ia >> received_vector;
//    unlink(pipe_from_python.c_str());  // Очистка канала
    return received_vector;
}

inline void send_vector_to_python(int id, const std::vector<POINT> &vec) {
    std::string pipe_to_python = "/tmp/drone_pipe_to_python_" + std::to_string(id);
    int fd = open(pipe_to_python.c_str(), O_WRONLY);

    std::ofstream ofs(pipe_to_python, std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << vec;
//   unlink(pipe_to_python.c_str());  // Очистка канала
}

inline void send_message_to_python(int id, const std::string &message) {
    std::string pipe_to_python = "/tmp/drone_pipe_to_python_" + std::to_string(id);

    // Открываем канал для записи
    int fd = open(pipe_to_python.c_str(), O_WRONLY);
    if (fd == -1) {
        std::cerr << "Failed to open pipe: " << pipe_to_python << std::endl;
        return;
    }

    // Сериализуем сообщение и отправляем его в канал
    std::ofstream ofs(pipe_to_python, std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << message;

    // Закрываем файл и очищаем канал
    ofs.close();
    close(fd);
//    unlink(pipe_to_python.c_str());
}

