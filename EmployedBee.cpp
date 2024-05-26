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
	// взятие нектара из источника
	moveToPoint(point);
	// сброс нектара
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
			return false; // точка слишком близко к другой точке
		}
	}
	return true; // точка находится на достаточном расстоянии от всех точек
}

FoodSource EmployedBee::generateNewFoodSource(const std::pair<POINT, POINT>& searchArea, const double minDistance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distX(searchArea.first.x, searchArea.second.x); // границы значений для генерации,
	std::uniform_real_distribution<double> distY(searchArea.second.y, searchArea.first.y); // чтобы точка лежала внутри пространства поиска

	POINT newPoint;
	do
	{
		newPoint = { distX(gen), distY(gen) };

	} while (!isValidPoint(newPoint, this->knownSources, minDistance));

	FoodSource newSource(newPoint); // создание экземпляра класса источника

	return newSource;
}

void EmployedBee::processBee()
{
	std::cout << "Employed Bee id " << this->id << " started scouting" << std::endl;
	std::shared_ptr<FoodSource> newSource;
	bool nectarFound = false; // пока что разведчиком не найден нектар
	do
	{
		newSource = std::make_shared<FoodSource>(this->generateNewFoodSource(this->searchArea, this->radius)); // генерация нового источника
		this->moveToPoint(newSource->getLocation()); // разведчик к нему отправляется
		nectarFound = this->scanNectar();
		if (!nectarFound) // если на этой точке не найден нектар, то мы ее осматриваем в большем радиусе
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
			else newSource->markAsAbandoned(); // если в радиусе ничего не найдено, то забрасываем
		}
	} while (!nectarFound); // повторяем генерацию, пока разведчик не найдет источник с нектаром
	std::cout << "Employed Bee id " << this->id << " started foraging" << std::endl;
	do
	{
		this->currentSource = newSources[0];
		// на предыдущем этапе у рабочего должен был появиться источник в памяти
		// отправка к источнику
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// сразу уносим нектар на точку сбора, потому что после генерации он гарантированно есть на источнике
		this->carryNectar(this->getCurrentSource(), this->destination);
		// отправка на танцпол
		this->moveToPoint(this->dancefloor);
		//передаем информацию о найденном источнике
		this->doWaggleDance(this->getCurrentSource());
		// возвращаемся к источнику, чтобы продолжить разведку местности вокруг
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// локальная разведка
		auto check = this->localSearch(this->getCurrentSource(), this->radius);
		if (check.size())
		{
			for (uint32_t i = 0; i < check.size(); i++)
				this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
		}
		else this->getCurrentSource()->markAsAbandoned();
		this->newSources.erase(this->newSources.begin());// удаление текущего источника из списка необработанных
														// и смещение всех элементов на начало
	} while (this->newSources.size()); //пока есть еще точки, ожидающие сбора нектара
	// когда больше нечего обрабатывать, итерация этого рабочего закончилась
	std::cout << "Employed Bee id " << this->id << " ended its work" << std::endl;
}

