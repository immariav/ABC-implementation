#include "EmployedBee.h"
#include <cmath>
#include <random>

EmployedBee::EmployedBee()
    : Bee(), searchArea{{0, 0}, {0, 0}}, destination{0, 0}, currentSource(nullptr) {}

EmployedBee::EmployedBee(const std::string& id, const POINT& dancefloor, double radius, const POINT& destination, const std::pair<POINT, POINT>& searchArea)
    : Bee(id, dancefloor, radius), destination(destination), searchArea(searchArea), currentSource(nullptr) {}

EmployedBee::~EmployedBee() {}

void EmployedBee::addSourceToConstMemory(std::shared_ptr<FoodSource> source)
{
	this->knownSources.push_back(source);
}

void EmployedBee::carryNectar(std::shared_ptr<FoodSource> source, const POINT point)
{
	// ������ ������� �� ���������
	//moveToPoint(point);
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

	return FoodSource (newPoint);
}

void EmployedBee::processBee()
{
	// drone is already armed and flying
	std::cout << "Employed Bee id " << this->id << " started scouting" << std::endl;
	std::shared_ptr<FoodSource> newSource;
	bool nectarFound = false; // it is not found yet
	do
	{
		newSource = std::make_shared<FoodSource>(this->generateNewFoodSource(this->searchArea, this->radius)); // ��������� ������ ���������
		this->knownSources.push_back(newSource);
		moveToPoint(this->sock, this->addr, newSource->getLocation()); // going to the generated point
		nectarFound = this->scanNectar(); // check if it is a source itself
		if (!nectarFound) // if not, flying around and trying to find nectar
		{
			auto& check = this->localSearch(newSource, this->radius); // vector of the nectar sources found during local search
			if (!check.empty()) // if not empty
			{
                for (const auto& point : check) {
                    auto newFoodSource = std::make_shared<FoodSource>(point);
                    newSources.push_back(newFoodSource); // add to the temporary memory
                    knownSources.push_back(newFoodSource); // and to the const 
                }
				nectarFound = true;
			}
			else newSource->markAsAbandoned(); // if no nectar then this source is empty on the whole radius
		}
	} while (!nectarFound); // repeat until it finds anything


	std::cout << "Employed Bee id " << this->id << " started foraging" << std::endl;
	while (!newSources.empty()) {
        currentSource = newSources.front(); // working on the first of the found
		moveToPoint(this->sock, this->addr, currentSource->getLocation()); // going to the chosen point
//		carryNectar(currentSource, destination);
 //       moveToPoint(dancefloor);
        doWaggleDance(currentSource);
//		moveToPoint(currentSource->getLocation());
        auto& check = localSearch(currentSource, radius);
        for (const auto& point : check) {
            auto newFoodSource = std::make_shared<FoodSource>(point);
            newSources.push_back(newFoodSource);
            knownSources.push_back(newFoodSource);
    	}

        newSources.erase(newSources.begin());
    }
	std::cout << "Employed Bee id " << this->id << " ended its work" << std::endl;
}

