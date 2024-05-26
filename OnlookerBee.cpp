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
    if (this->activeSources.size() > 1) // ���������� ����� ���������� ������, ���� ���� �� ���� ��������, ����� ������� ������ �������� 
        this->chooseFoodSource();
    else this->chosenSource = this->activeSources[0];
    this->activeSources.clear(); // ����� ������, ������ ���������� �� ���� �������� ���������� �� �����
    this->newSources.push_back(this->chosenSource);
    std::cout << "Onlooker Bee id " << this->id << " chose a source" << std::endl;
    do
    {
        this->moveToPoint(this->chosenSource->getLocation());
        auto& check = this->localSearch(this->chosenSource, this->radius * 1.5); // ����� ����������� ������ � ������� �� r �� 1.5r
        // ��������, ����� ����� �������������� ������� ��������� �������� ��� �����������
        if (check.size())
        {
            for (uint32_t i = 0; i < check.size(); i++)
            {
                this->newSources.push_back(std::make_shared<FoodSource>(check[i]));
            }
            this->moveToPoint(this->chosenSource->getLocation()); //  ������������ �� �������� � �������� ����� � ���������
            for (uint32_t i = 0; i < check.size(); i++)
                this->doWaggleDance(newSources[i]);
            // watchWaggleDance();
        }
        else this->chosenSource->markAsAbandoned();
        this->newSources.erase(this->newSources.begin()); // �������� �������� ��������� �� ������ ��������������
                                                            // � �������� ���� ��������� �� ������
        if(this->newSources.size())
            this->chosenSource = this->newSources[0];
    } while (this->newSources.size()); 
    std::cout << "Onlooker Bee id " << this->id << " ended foraging" << std::endl;
    // ����� ������ ������ ������������, ������������ �� ������� 
    this->moveToPoint(this->dancefloor);
    std::cout << "Onlooker Bee id " << this->id << " returned to the dancefloor" << std::endl;
}

