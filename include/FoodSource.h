#pragma once
#include <cstdint>
#include <vector>
#include "Shapes.h"
#include <utility>
#include <memory>

class FoodSource
{
private:

	bool isAbandoned;
	POINT location;

public:

	FoodSource();
	FoodSource(POINT point);
	~FoodSource();

	void markAsAbandoned();

	POINT getLocation() const;

	//true - abandoned, false - active
	bool getAbandonedStatus();
};

