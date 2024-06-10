# Файл drone_controler.py

import math
import os
import random
import time
# ---------------------------------------------------------------------
# ---------------------------------------------------------------------
from dronekit import connect, VehicleMode, LocationGlobalRelative

# Функция для генерации n случайных точек в пределах прямоугольника        
def generate_random_points(n, top_left, bottom_right):
    points = []
    for _ in range(n):
        x = random.uniform(top_left[0], bottom_right[0])
        y = random.uniform(top_left[1], bottom_right[1])
        points.append((x, y))
    return points

    # Функция для чтения координат из файла
def read_coordinates_from_file(file_path):
    coordinates = []
    with open(file_path, 'r') as file:
        for line in file:
            x, y = map(float, line.strip().split(','))
            coordinates.append((x, y))
    return coordinates

    # Функция для вычисления расстояния между двумя точками
def distance(point1, point2):
    return math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)

class DroneController:
    def __init__(self, drone_id, base_port=14550):
        self.drone_id = drone_id
        self.port = base_port + drone_id
        self.connection_string = f'127.0.0.1:{self.port}'
        self.vehicle = None
    
    def connect(self):
        print(f"Connecting to drone{self.drone_id} on: {self.connection_string}")
        self.vehicle = connect(self.connection_string, wait_ready=True)

    def arm_and_takeoff(self, target_altitude):
        print(f"Drone{self.drone_id}: Arming motors")
        while not self.vehicle.is_armable:
            print(f"Drone{self.drone_id}: Waiting for vehicle to initialise...")
            time.sleep(1)
        
        self.vehicle.mode = VehicleMode("GUIDED")
        self.vehicle.armed = True

        while not self.vehicle.armed:
            print(f"Drone{self.drone_id}: Waiting for arming...")
            time.sleep(1)

        print(f"Drone{self.drone_id}: Taking off!")
        self.vehicle.simple_takeoff(target_altitude)
        
        while True:
            print(f"Drone{self.drone_id} Altitude: {self.vehicle.location.global_relative_frame.alt}")
            if self.vehicle.location.global_relative_frame.alt >= target_altitude * 0.8:
                print(f"Drone{self.drone_id} Reached target altitude")
                break
            time.sleep(1)

    def goto(self, lat, lon):
        print(f"Drone{self.drone_id}: Going to location")
        point = LocationGlobalRelative(lat, lon)
        self.vehicle.simple_goto(point)

    def land(self):
        print(f"Drone{self.drone_id}: Landing")
        self.vehicle.mode = VehicleMode("LAND")

    def close(self):
        print(f"Drone{self.drone_id}: Closing connection")
        self.vehicle.close()
        
    # Локальная разведка
    def local_search(self, spiral_coordinates, sources_locations):
        output_coordinates = []
        
        for target_coordinate in spiral_coordinates:
            target_location = LocationGlobalRelative(target_coordinate[0], target_coordinate[1], 0)
            self.vehicle.simple_goto(target_location)
            
            while True:
                current_location = self.vehicle.location.global_relative_frame
                current_coordinate = (current_location.lon, current_location.lat)
                
                if distance(current_coordinate, target_coordinate) < 1:
                    for source_location in sources_locations:
                        if distance(current_coordinate, source_location) < 1:
                            output_coordinates.append(source_location)
                    break
                
                time.sleep(1)
                
        return output_coordinates
     
    def scan_nectar(self, sources_locations, tolerance=10):
        current_location = self.vehicle.location.global_relative_frame
        current_coordinate = (current_location.lon, current_location.lat)
        
        for source_location in sources_locations:
            if self.distance(current_coordinate, source_location) <= tolerance:
                return True
        
        return False
        
    
