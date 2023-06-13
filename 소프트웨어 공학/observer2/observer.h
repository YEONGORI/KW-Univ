#ifndef OBSERVER_H
#define OBSERVER_H

#include "subject.h"

#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Observer
{
public:
	Observer(){};
	virtual void update(Subject *subject) = 0;
};

class ConcreteObserver : public Observer
{
public:
	ConcreteObserver(string newname);
	void attachSubject(ConcreteSubject *subject);
	void detachSubject(ConcreteSubject *subject);
	virtual void update(Subject *subject);

private:
	list<ConcreteSubject *> subjects;
	string name;
};
ConcreteObserver::ConcreteObserver(string newname) : Observer(), subjects(NULL), name(newname){};
void ConcreteObserver::attachSubject(ConcreteSubject *subject)
{
	subjects.push_back(subject);
	subject->attach(this);
};
void ConcreteObserver::detachSubject(ConcreteSubject *subject)
{
	subjects.erase(find(subjects.begin(), subjects.end(), subject));
	subject->detach(this);
	cout << "Subject detached!" << endl;
};
void ConcreteObserver::update(Subject *subject)
{
	list<ConcreteSubject *>::iterator iter;
	iter = find(subjects.begin(), subjects.end(), subject);
	if (iter != subjects.end())
		cout << "Observer " << name << " queries Subject " << (*iter)->getName() << " for new state " << (*iter)->getState() << endl;
}
#endif