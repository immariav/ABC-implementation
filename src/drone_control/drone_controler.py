# Файл drone_controler.py

import os
# Функция для создания именованного канала
def create_fifo(fifo_path):
    try:
        os.mkfifo(fifo_path)
    except FileExistsError:
        pass

# Функция для удаления именованного канала
def close_fifo(fifo_path):
    try:
        os.unlink(fifo_path)
    except FileNotFoundError:
        pass

# Функция для записи данных в именованный канал
def write_to_fifo(fifo_path, data):
    with open(fifo_path, 'w') as fifo_out:
        fifo_out.write(data)

# Функция для чтения данных из именованного канала
def read_from_fifo(fifo_path):
    with open(fifo_path, 'r') as fifo_in:
        data = fifo_in.read()
    return data

# ---------------------------------------------------------------------

from dronekit import connect, VehicleMode

# Функция для установки режима GUIDED и взлета на заданную высоту
def takeoff_and_guided_mode(connection_string, altitude):
    # Подключение к дрону
    vehicle = connect(connection_string, wait_ready=True)
    
    # Установка режима GUIDED
    vehicle.mode = VehicleMode("GUIDED")
    
    # Взлет на заданную высоту
    vehicle.simple_takeoff(altitude)

    # Ожидание достижения заданной высоты
    while not vehicle.location.global_relative_frame.alt >= altitude * 0.95:
        pass
    
    # Завершение соединения
    vehicle.close()

