#include <cstdlib>

#include "job.h"

Job::Job(const int id, const int length) 
{ 
	this->id = id;
	this->length = length;
	machine = 0;
}

int Job::getId(void) const
{
	return id;
}

int Job::getLength(void) const
{
	return length;
}

Machine* Job::getMachine(void) const 
{
	return machine;
}

void Job::setMachine(Machine *machine) 
{
	this->machine = machine;
}

bool Job::operator< (const Job& other) const 
{
	return length > other.length;
}
