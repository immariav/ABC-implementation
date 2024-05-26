#pragma once
#include <vector>
#include "FoodSource.h"
#include <cstdint>
#include <string>

class Bee
{
protected:

	std::string id;
	POINT dancefloor; // координаты танцпола
	double radius; // минимальное расстояние между источниками и радиус разведки
	std::vector<std::shared_ptr<FoodSource>> newSources; // новые источники, которые могут быть найдены в процессе локальной разведки

public:

	Bee();
	Bee(const std::string id, POINT& dancefloor,  double radius);
	~Bee();

	// передвижение в указанную точку
	void moveToPoint(const POINT& point); 
	// передаем от пчелы к пчеле информацию об источнике из памяти
	void doWaggleDance(const std::shared_ptr<FoodSource> source); 
	// распознавание нектара. true - найден в указанной точке
	bool scanNectar();
	// поиск нектара в точке в заданном радиусе
	std::vector<POINT>& localSearch(std::shared_ptr<FoodSource> source, double radius); 
	// функция обработки пчелы (переопределена для каждого дочернего класса)
	virtual void processBee();
	// добавление источника в память (переопределена для каждого дочернего класса, поскольку память представлена по-разному)
	virtual void addSourceToMemory(std::shared_ptr<FoodSource> source);
};

