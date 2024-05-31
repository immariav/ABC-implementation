#pragma once
#include <cstdint>
#include <string>
#include <set>
#include "EmployedBee.h"
#include "OnlookerBee.h"
#include <utility>
#include <memory>

class Hive
{
private:

	uint32_t swarmSize; // ������ ���
	uint32_t onlookersQty; // ���������� ������������
	uint32_t employeesQty; // ���������� �������

	std::vector<std::unique_ptr<OnlookerBee>> onlookers; // ������ ���������� �� ������������ 
	std::vector<std::unique_ptr<EmployedBee>> employees; // ������ ���������� �� ������� 

	uint32_t currentNectarAmount; // ������� ���������� �������
	uint32_t goal; // ������� �������

	double minDistBetweenSources; // ����������� ��������� ���������� ����� �����������

	POINT destinationPoint; // ����� ����� ���������
	POINT dancefloor; // ���������� ��������

	std::pair<POINT, POINT> searchArea; // ������� (������������ ������)

	// �������� ��������� ��������� �������� �� ������������
	bool isValidSearchArea(double xTopLeft, double yTopLeft, double xBottomRight, double yBottomRight); 

	// ����� ����� ������ ���� �� ������������� ������
	bool isPointOutsideSA(const POINT& point, const POINT& topLeft, const POINT& bottomRight);

	//��� ����������������� ���������
	void processEmployees();
	void processOnlookers();

public:

	Hive();
	~Hive();

	void setSwarmSize(uint32_t size);
	void setGoal(uint32_t goal);
	void setDestinationPoint(double x, double y);
	void setSearchArea(const POINT& topLeft, const POINT& bottomRight);
	void setSearchArea(double xTopLeft, double yToppLeft, double xBottomRight, double yBottomRight);

	uint32_t getGoal() const;
	POINT getSearchAreaTopLeft() const;
	POINT getSearchAreaBottomRight() const;
	double getSearchAreaWidth() const;
	double getSearchAreaHeight() const;
	double getMinDistBetweenSources() const;
	POINT getDancefloorPoint() const;
	// �������, ������� ����� ����������� ������� ����� �������
	void increaseCurrentNectarAmoiunt();

	// ������������� ������ �������� ������������ ����
	void initializeDrones(const std::vector<std::string>& droneIds); 

	// �������� ������ ���������
	void Solve(); 
};

