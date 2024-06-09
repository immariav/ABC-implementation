#include "EmployedBee.h"
#include <cmath>
#include <random>


EmployedBee::EmployedBee(const int id) : Bee(id){}

EmployedBee::~EmployedBee() {}

// void EmployedBee::addSourceToConstMemory(std::shared_ptr<FoodSource> source)
// {
// 	this->knownSources.push_back(source);
// }

void EmployedBee::carryNectar(std::shared_ptr<FoodSource> source, const POINT point)
{
	// ������ ������� �� ���������
	//moveToPoint(point);
	// ����� �������
}

bool EmployedBee::checkNectar()
{
    return false;
}

double EmployedBee::distance(const POINT& p1, const POINT& p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool EmployedBee::isValidPoint(const POINT& newPoint, const std::vector<std::shared_ptr<FoodSource>>& sources, double minDistance)
{
	for (const auto& source : sources) {
		if (distance(newPoint, source->getLocation()) < minDistance) {
			return false; // 
		}
	}
	return true; // 
}

FoodSource EmployedBee::generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double radius)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distX(searchArea.first.x, searchArea.second.x); // ������� �������� ��� ���������,
	std::uniform_real_distribution<double> distY(searchArea.second.y, searchArea.first.y); // ����� ����� ������ ������ ������������ ������

	POINT newPoint;
	do
	{
		newPoint = { distX(gen), distY(gen) };

	} while (!isValidPoint(newPoint, this->knownSources, radius * sqrt(2)));

	return FoodSource (newPoint);
}

std::vector<POINT> &EmployedBee::localSearch(const POINT &, double radius)
{
        static std::vector<POINT> points = {}; // Placeholder, replace with actual implementation
	// move to the this->currentSource->getLocation();
    return points;
}

void EmployedBee::processBee()
{
	// drone is already armed and flying
	std::cout << "Employed Bee id " << this->id << " started scouting" << std::endl;
	
	std::shared_ptr<FoodSource> newSource =
	std::make_shared<FoodSource>(generateNewFoodSource(searchArea, radius)); 
	this->knownSources.push_back(newSource);
	this->sourcesToCheck.push_back(newSource);
	currentSource = newSource;
	doWaggleDance(sourcesToCheck); //newSource (сагитировал наблюдателя)
//	moveToPoint(currentSource->getLocation()); // going to the generated point
	
	while (!sourcesToCheck.empty())
	{
		moveToPoint(currentSource->getLocation());

		if(checkNectar())
			carryNectar(newSource, destination);
		
		localSearch(this->currentSource->getLocation(), this->radius); 

		watchWaggleDance(); // waiting on the point

		doWaggleDance(sourcesToShare);

		sourcesToCheck.erase(sourcesToCheck.begin());
		currentSource = sourcesToCheck.front();
	}

	std::cout << "Employed Bee id " << this->id << " ended its work" << std::endl;
}

