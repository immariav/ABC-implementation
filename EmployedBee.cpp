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
	// ������ ������� �� ���������
	moveToPoint(point);
	// ����� �������
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
		// �� ���������� ����� � �������� ������ ��� ��������� �������� � ������ (����� ���������� ��������� �����)
		// ��� ������� ��� �� ������������ �� newSources
		// �������� � ���������
		this->moveToPoint(this->getCurrentSource()->getLocation());
		// ����� ������ ������ �� ����� �����, ������ ��� ����� ��������� ����������� �� �������������� ���� �� ���������
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
	// ����� ������ ������ ������������, ������������ �� ������� 
	this->moveToPoint(this->dancefloor);
}

