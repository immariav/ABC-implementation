#pragma once
#include <vector>
#include "FoodSource.h"
#include <cstdint>
#include <string>
#include <iostream>

class Bee
{
protected:

	std::string id;
	POINT dancefloor; // ���������� ��������
	double radius; // ����������� ���������� ����� ����������� � ������ ��������
	std::vector<std::shared_ptr<FoodSource>> newSources; // ����� ���������, ������� ����� ���� ������� � �������� ��������� ��������
	POINT currentPosition; // ������� ���������� �����

public:

	Bee();
	Bee(const std::string id, POINT& dancefloor,  double radius);
	~Bee();

	// ������������ � ��������� �����
	void moveToPoint(const POINT& point); 
	// �������� �� ����� � ����� ���������� �� ��������� �� ������
	void doWaggleDance(const std::shared_ptr<FoodSource> source); 
	// ������������� �������. true - ������ � ��������� �����
	bool scanNectar();
	// ����� ������� � ����� � �������� �������
	std::vector<POINT>& localSearch(std::shared_ptr<FoodSource> source, double radius); 
	// ������� ��������� ����� (�������������� ��� ������� ��������� ������)
	virtual void processBee();
	// ���������� ��������� � newSources
	void addSourceToTempMemory(std::shared_ptr<FoodSource> source);
};

