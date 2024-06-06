// C++ - Python API
#pragma once
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

// Функция для создания канала
inline void createFifo(const std::string& fifo_path) { //"/tmp/my_fifo"
    mkfifo(fifo_path.c_str(), 0666);
}

// Функция для закрытия канала
inline void closeFifo(const std::string& fifo_path) {
    unlink(fifo_path.c_str());
}

// Функция для записи данных в канал
inline void writeToFifo(const std::string& fifo_path, const std::string& data) {
    std::ofstream fifo_out(fifo_path);
    fifo_out << data;
    fifo_out.close();
}

// Функция для чтения данных из канала
inline std::string readFromFifo(const std::string& fifo_path) {
    std::ifstream fifo_in(fifo_path);
    std::string data;
    getline(fifo_in, data);
    fifo_in.close();
    return data;
}