#include "EmployedBee.h"
#include <cmath>
#include <random>

EmployedBee::EmployedBee() : Bee()
{
	this->destination = { 0, 0 };
	this->currentSource = nullptr;
	this->searchArea.first = { 0,0 };
	this->searchArea.second = { 0,0 };
}

EmployedBee::EmployedBee(const std::string id, POINT& dancefloor, double radius, POINT& destination, std::pair<POINT, POINT>& searchArea)
	: Bee(id, dancefloor, radius)
{
	this->destination = { 0, 0 };
	this->currentSource = nullptr;
	this->searchArea = searchArea;
}

EmployedBee::~EmployedBee()
{
}

void EmployedBee::carryNectar(std::shared_ptr<FoodSource> source, const POINT& point)
{
	// ������ ������� �� ���������
	moveToPoint(point);
	// ����� �������
}

std::shared_ptr<FoodSource> EmployedBee::getCurrentSource()
{
	return this->currentSource;
}

double EmployedBee::distance(const POINT& p1, const POINT& p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool EmployedBee::isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance)
{
	for (const auto& source : sources) {
		if (distance(newPoint, source->getLocation()) < minDistance) {
			return false; // ����� ������� ������ � ������ �����
		}
	}
	return true; // ����� ��������� �� ����������� ���������� �� ���� �����
}

FoodSource EmployedBee::generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance)
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

void EmployedBee::processBee()
{
	std::cout << "Employed Bee id " << this->id << " started scouting" << std::endl;
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
	std::cout << "Employed Bee id " << this->id << " started foraging" << std::endl;
	do
	{
		this->currentSource = newSources[0];
		// �� ���������� ����� � �������� ������ ��� ��������� �������� � ������
		// �������� � ���������
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// ����� ������ ������ �� ����� �����, ������ ��� ����� ��������� �� �������������� ���� �� ���������
		this->carryNectar(this->getCurrentSource(), this->destination);
		// �������� �� �������
		this->moveToPoint(this->dancefloor);
		//�������� ���������� � ��������� ���������
		this->doWaggleDance(this->getCurrentSource());
		// ������������ � ���������, ����� ���������� �������� ��������� ������
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// ��������� ��������
		auto check = this->localSearch(this->getCurrentSource(), this->radius);
		if (check.size())
		{
			for (uint32_t i = 0; i < check.size(); i++)
				this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
		}
		else this->getCurrentSource()->markAsAbandoned();
		this->newSources.erase(this->newSources.begin());// �������� �������� ��������� �� ������ ��������������
														// � �������� ���� ��������� �� ������
	} while (this->newSources.size()); //���� ���� ��� �����, ��������� ����� �������
	// ����� ������ ������ ������������, �������� ����� �������� �����������
	std::cout << "Employed Bee id " << this->id << " ended its work" << std::endl;
}

