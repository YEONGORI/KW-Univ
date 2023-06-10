#include "observer.h"
#include "subject.h"

int main()
{
	ConcreteSubject s1("s1");
	ConcreteSubject s2("s2");
	ConcreteObserver o1("o1");
	ConcreteObserver o2("o2");
	ConcreteObserver o3("o3");
	o1.attachSubject(&s1);
	o1.attachSubject(&s2);
	o2.attachSubject(&s1);
	o3.attachSubject(&s2);
	s1.setState(5);
	s2.setState(2);
}