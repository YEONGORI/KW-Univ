#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>

#include "observer.h"

using namespace std;

class Subject
{
private:
	list<Observer *> observers;

public:
	virtual ~Subject(){};

	void attach(Observer *obs)
	{
		observers.push_back(obs);
	}

	void detach(Observer *obs)
	{
		observers.erase(find(observers.begin(), observers.end(), obs));
	}

	void notify()
	{
		for (list<Observer *>::iterator iter = observers.begin();
			 iter != observers.end(); ++iter)
		{
			(*iter)->update(this);
		};
	}
};

class ConcreteSubject : public Subject
{
public:
	ConcreteSubject(string newname);
	void setState(int newstate);
	int getState();
	string getName();

private:
	int state;
	string name;
};
ConcreteSubject::ConcreteSubject(string newname) : Subject(), name(newname), state(0){};
void ConcreteSubject::setState(int newstate)
{
	state = newstate;
	notify(); // notify all observers that state
			  // has changed
}
int ConcreteSubject::getState()
{
	return state;
}
string ConcreteSubject::getName()
{
	return name;
}

#endif