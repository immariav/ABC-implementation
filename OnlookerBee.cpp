#include "OnlookerBee.h"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime> 

OnlookerBee::OnlookerBee() : Bee()
{
    this->knownSources = {};
    this->chosenSource = nullptr;
}

OnlookerBee::OnlookerBee(const std::string id, POINT& dancefloor, double radius, POINT& destination)
    : Bee(id, dancefloor, radius)
{
    this->knownSources = {};
    this->chosenSource = nullptr;
}

OnlookerBee::~OnlookerBee()
{
}

void OnlookerBee::chooseFoodSource()
{
    //просмотр всех источников из памяти и создание временного вектора активных
    std::vector<std::shared_ptr<FoodSource>> activeSources;
    for (const auto& source : this->knownSources) {
        if (!source->getAbandonedStatus()) {
            activeSources.push_back(source);    
        }
    }
    // рулеточный отбор из knownSources источника с равными шансами
    this->chosenSource = activeSources[rand() % knownSources.size()];
    activeSources.clear();
}

void OnlookerBee::addSourceToMemory(std::shared_ptr<FoodSource> source)
{
    this->knownSources.push_back(source);
}

std::shared_ptr<FoodSource> OnlookerBee::getChosenSource()
{
    return this->chosenSource;
}

void OnlookerBee::processBee()
{
    //на предыдущем этапе память наблюдателя пополняется различными источниками (после выполнения пчелиного танца)
    // или остался еще не обработанный из newSources
    this->chooseFoodSource();
    this->newSources.push_back(this->chosenSource);
    do
    {
        this->moveToPoint(this->getChosenSource()->getLocation());
        auto check = this->localSearch(this->getChosenSource(), this->radius);
        if (check.size())
        {
            for (uint32_t i = 0; i < check.size(); i++)
            {
                this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
                this->doWaggleDance(newSources[i]); // сообщаем рабочему об источнике
            }
        }
        else this->chosenSource->markAsAbandoned();
        this->chosenSource = this->newSources[0];
        this->newSources.erase(this->newSources.begin()); // удаление текущего источника из списка необработанных
                                                            // и смещение всех элементов на начало
    } while (this->newSources.size()); 
    // когда больше нечего обрабатывать, возвращаемся на танцпол 
    this->moveToPoint(this->dancefloor);
}

