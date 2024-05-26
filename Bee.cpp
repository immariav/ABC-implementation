#include "Bee.h"

Bee::Bee()
{
	this->id = "";
	this->dancefloor = { 0, 0 };
	this->currentPosition = { 0, 0 };
	this->radius = 0;
	this->newSources = {};
}

Bee::Bee(const std::string id, POINT& dancefloor, double radius)
{
	this->id = id;
	this->dancefloor = dancefloor;
	this->radius = radius;
	this->newSources = {};
	this->currentPosition = { 0, 0 };
}

Bee::~Bee()
{
}

void Bee::moveToPoint(const POINT& point)
{
	// передвижение в point
}

void Bee::doWaggleDance(const std::shared_ptr<FoodSource> source)
{
	// передача знаний об источнике между пчелами
	// новый источник заносится в память пчеле с помощью соответствующего метода
	// передача сообщения типа: первый цвет - количество источников (позволит сразу зарезервировать нужное количество мест в векторе), 
	// последующие цвета - x, y  источников последовательно
	// либо же: вместо координат - направление до источника и расстояние до него от текущей точки из памяти, 
	// а на основе полученной инфы принимающий дрон сам вычисляет его координаты и отправляется
}

bool Bee::scanNectar()
{
	// распознавание нектара
	// будет сравнивать текущую позицию дрона со списком нектара, который будет передаваться в конструкторы пчел
	return true; // пока что всегда возвращается true, чтобы комплитяор не ругался
}

std::vector<POINT>& Bee::localSearch(std::shared_ptr<FoodSource> source, double radius)
{
	double x = 0; double y = 0;
	bool nectarFound = false;
	std::vector<POINT> sourceLocations;
	// поиск в пределах radius от точки source->getLocation(). нужно облететь всю территорию
	// если найден нектар, то добавляем координаты в вектор
	if (nectarFound)
	{
		sourceLocations.push_back({ x , y });
	}
	return sourceLocations;
}

void Bee::processBee()
{
}

void Bee::addSourceToTempMemory(std::shared_ptr<FoodSource> source)
{
	this->newSources.push_back(source);
}

