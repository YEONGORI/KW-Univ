#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include "observer.h"

class Shop : IObserver
{
	// Name of the Shop
	std::string name;
	float price;

public:
	Shop(std::string n);
	void Update(float price);
};

Shop::Shop(std::string name)
{
	this->name = name;
}

void Shop::Update(float price)
{
	this->price = price;

	// Lets print on console just to test the working
	std::cout << "Price at " << name << " is now " << price << "\n";
}

#endif
