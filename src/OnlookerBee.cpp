#include <iostream>
#include <vector>
#include <cstdlib> 
#include <random>
#include <vector>
#include <memory>
#include "OnlookerBee.h"

OnlookerBee::OnlookerBee()
    : Bee(), chosenSource(nullptr) {}

OnlookerBee::OnlookerBee(const std::string& id, POINT& dancefloor, double radius)
    : Bee(id, dancefloor, radius), chosenSource(nullptr) {}

OnlookerBee::~OnlookerBee() {}

void OnlookerBee::chooseFoodSource()
{
    // ���������� ����� �� knownSources ��������� � ������� �������
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
    // �����-�� �������� �������������, ������� ����� ������� ������� ��� ���������� �������� ������
    // watchWaggleDance();
    // ��������� �� ������ ���������� � activeSources 
    if (activeSources.size() > 1) {
        chooseFoodSource();
    } else if (!activeSources.empty()) {
        chosenSource = activeSources.front();
    }

    activeSources.clear();
    newSources.push_back(chosenSource);
    std::cout << "Onlooker Bee id " << this->id << " chose a source" << std::endl;
    
    while (!newSources.empty()) {
 //       moveToPoint(chosenSource->getLocation());
        auto& check = localSearch(chosenSource, radius * 1.5);

        if (!check.empty()) {
            for (const auto& point : check) {
                auto newFoodSource = std::make_shared<FoodSource>(point);
                newSources.push_back(newFoodSource);
            }
 //           moveToPoint(chosenSource->getLocation());
            for (const auto& source : newSources) {
                doWaggleDance(source);
            }
        } else {
            chosenSource->markAsAbandoned();
        }

        newSources.erase(newSources.begin());
        if (!newSources.empty()) {
            chosenSource = newSources.front();
        }
    }
    
    std::cout << "Onlooker Bee id " << this->id << " ended foraging" << std::endl;
    // ����� ������ ������ ������������, ������������ �� ������� 
 //   this->moveToPoint(this->dancefloor);
    std::cout << "Onlooker Bee id " << this->id << " returned to the dancefloor" << std::endl;
}

