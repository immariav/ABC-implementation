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
	// ������������ � point
}

void Bee::doWaggleDance(const std::shared_ptr<FoodSource> source)
{
	// �������� ������ �� ��������� ����� �������
	// ����� �������� ��������� � ������ ����� � ������� ���������������� ������
	// �������� ��������� ����: ������ ���� - ���������� ���������� (�������� ����� ��������������� ������ ���������� ���� � �������), 
	// ����������� ����� - x, y  ���������� ���������������
	// ���� ��: ������ ��������� - ����������� �� ��������� � ���������� �� ���� �� ������� ����� �� ������, 
	// � �� ������ ���������� ���� ����������� ���� ��� ��������� ��� ���������� � ������������
}

bool Bee::scanNectar()
{
	// ������������� �������
	// ����� ���������� ������� ������� ����� �� ������� �������, ������� ����� ������������ � ������������ ����
	return true; // ���� ��� ������ ������������ true, ����� ���������� �� �������
}

std::vector<POINT>& Bee::localSearch(std::shared_ptr<FoodSource> source, double radius)
{
	double x = 0; double y = 0;
	bool nectarFound = false;
	std::vector<POINT> sourceLocations;
	// ����� � �������� radius �� ����� source->getLocation(). ����� �������� ��� ����������
	// ���� ������ ������, �� ��������� ���������� � ������
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

