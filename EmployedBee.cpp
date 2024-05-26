#include "EmployedBee.h"

EmployedBee::EmployedBee() : Bee()
{
	this->destination = { 0, 0 };
	this->currentSource = nullptr;
}

EmployedBee::EmployedBee(const std::string id, POINT& dancefloor, double radius, POINT& destination) 
	: Bee(id, dancefloor, radius)
{
	this->destination = { 0, 0 };
	this->currentSource = nullptr;
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

void EmployedBee::processBee()
{
	do
	{
		this->currentSource = newSources[0];
		// на предыдущем этапе у рабочего должен был появиться источник в памяти (после выполнения пчелиного танца)
		// или остался еще не обработанный из newSources
		// отправка к источнику
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// сразу уносим нектар на точку сбора, потому что после генерации разведчиком он гарантированно есть на источнике
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
	// когда больше нечего обрабатывать, возвращаемся на танцпол 
	this->moveToPoint(this->dancefloor);
}

