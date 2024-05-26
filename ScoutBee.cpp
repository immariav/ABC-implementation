#include "ScoutBee.h"
#include <corecrt_math.h>
#include <cmath>
#include <random>

ScoutBee::ScoutBee() : Bee()
{
	this->searchArea.first = { 0, 0 };
	this->searchArea.second = { 0, 0 };
	this->knownSources = {};
}

ScoutBee::ScoutBee(const std::string id, POINT& dancefloor, double radius, std::pair<POINT, POINT>& searchArea) 
	: Bee(id, dancefloor, radius)
{
	this->searchArea = searchArea;
	this->knownSources = {};
	this->newSources = {};
}

ScoutBee::~ScoutBee()
{
}

double ScoutBee::distance(const POINT& p1, const POINT& p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool ScoutBee::isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance)
{
	for (const auto& source : sources) {
		if (distance(newPoint, source->getLocation()) < minDistance) {
			return false; // ����� ������� ������ � ������ �����
		}
	}
	return true; // ����� ��������� �� ����������� ���������� �� ���� �����
}

FoodSource ScoutBee::generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distX(searchArea.first.x, searchArea.second.x); // ������� �������� ��� ���������,
	std::uniform_real_distribution<double> distY(searchArea.second.y, searchArea.first.y); // ����� ����� ������ ������ ������������ ������

	POINT newPoint;
	do
	{
		newPoint = { distX(gen), distY(gen) };

	} while (!isValidPoint(newPoint, this->knownSources, minDistance));

	FoodSource newSource(newPoint); // �������� ���������� ������ ���������

	return newSource;
}

void ScoutBee::processBee()
{
	std::shared_ptr<FoodSource> newSource;
	bool nectarFound = false; // ���� ��� ����������� �� ������ ������
	do
	{
		newSource = std::make_shared<FoodSource>(this->generateNewFoodSource(this->searchArea, this->radius)); // ��������� ������ ���������
		this->moveToPoint(newSource->getLocation()); // ��������� � ���� ������������
		nectarFound = this->scanNectar();
		if (!nectarFound) // ���� �� ���� ����� �� ������ ������, �� �� �� ����������� � ������� �������
		{
			auto check = this->localSearch(newSource, this->radius);
			if (check.size())
			{
				for (uint32_t i = 0; i < check.size(); i++)
				{
					this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
					this->knownSources.push_back(newSources[i]);
				}
					
				nectarFound = true;
			}
			else newSource->markAsAbandoned(); // ���� � ������� ������ �� �������, �� �����������
		}
	} while (!nectarFound); // ��������� ���������, ���� ��������� �� ������ �������� � ��������
	this->moveToPoint(this->dancefloor); // ������������ �� �������
	for(uint32_t i = 0; i < this->newSources.size(); i++)
		this->doWaggleDance(this->newSources[i]); // ��������� ����� ��� �������� ����������
	this->newSources = {};
}

