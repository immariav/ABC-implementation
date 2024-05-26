#include "OnlookerBee.h"
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <random>
#include <vector>
#include <memory>

OnlookerBee::OnlookerBee() : Bee()
{
    this->chosenSource = nullptr;
}

OnlookerBee::OnlookerBee(const std::string id, POINT& dancefloor, double radius, POINT& destination)
    : Bee(id, dancefloor, radius)
{
    this->chosenSource = nullptr;
}

OnlookerBee::~OnlookerBee()
{
}

void OnlookerBee::chooseFoodSource()
{
    // рулеточный отбор из knownSources источника с равными шансами
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dist(0, this->activeSources.size() - 1);
    this->chosenSource = this->activeSources[dist(gen)];
}

std::shared_ptr<FoodSource> OnlookerBee::getChosenSource()
{
    return this->chosenSource;
}

void OnlookerBee::processBee()
{
    std::cout << "Onlooker Bee id " << this->id << " started working" << std::endl;
    // какой-то механизм синхронизации, который будет ожидать рабочих для исполнения пчелиных танцев
    // watchWaggleDance();
    // источники из танцев помещаются в activeSources 
    if (this->activeSources.size() > 1) // рулеточный отбор необходимо делать, если есть из чего выбирать, иначе берется первый источник 
        this->chooseFoodSource();
    else this->chosenSource = this->activeSources[0];
    this->activeSources.clear(); // выбор сделан, больше информация об этих активных источниках не нужна
    this->newSources.push_back(this->chosenSource);
    std::cout << "Onlooker Bee id " << this->id << " chose a source" << std::endl;
    do
    {
        this->moveToPoint(this->chosenSource->getLocation());
        auto& check = this->localSearch(this->chosenSource, this->radius * 1.5); // нужно осматривать кольцо в радиусе от r до 1.5r
        // возможно, нужно будет переопределить функцию локальной разведки для наблюдателя
        if (check.size())
        {
            for (uint32_t i = 0; i < check.size(); i++)
            {
                this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
            }
            this->moveToPoint(this->chosenSource->getLocation()); //  возвращаемся на источник и сообщаем дрону о найденных
            for (uint32_t i = 0; i < check.size(); i++)
                this->doWaggleDance(newSources[i]);
            // watchWaggleDance();
        }
        else this->chosenSource->markAsAbandoned();
        this->newSources.erase(this->newSources.begin()); // удаление текущего источника из списка необработанных
                                                            // и смещение всех элементов на начало
        if(this->newSources.size())
            this->chosenSource = this->newSources[0];
    } while (this->newSources.size()); 
    std::cout << "Onlooker Bee id " << this->id << " ended foraging" << std::endl;
    // когда больше нечего обрабатывать, возвращаемся на танцпол 
    this->moveToPoint(this->dancefloor);
    std::cout << "Onlooker Bee id " << this->id << " returned to the dancefloor" << std::endl;
}

