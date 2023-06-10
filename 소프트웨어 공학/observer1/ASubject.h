#ifndef ASUBJECT_H
#define ASUBJECT_H

#include <vector>
#include <algorithm>

using namespace std;

class ASubject
{
	// Lets keep a track of all the shops we have observing
	std::vector<Shop *> list;

public:
	void Attach(Shop *product);
	void Detach(Shop *product);
	void Notify(float price);
};

// CPP File

void ASubject::Attach(Shop *shop)
{
	list.push_back(shop);
}
void ASubject::Detach(Shop *shop)
{
	list.erase(std::remove(list.begin(), list.end(), shop), list.end());
}

void ASubject::Notify(float price)
{
	for (vector<Shop *>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(price);
		}
	}
}

class DummyProduct : public ASubject
{
public:
	void ChangePrice(float price);
};

void DummyProduct::ChangePrice(float price)
{
	Notify(price);
}

#endif
