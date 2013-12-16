#include "machine.h"

using namespace std;

Machine::Machine(const int id) 
{ 
	this->id = id;
	occupation = 0;
}

int Machine::getId(void) const
{
	return id;
}

int Machine::getOccupation(void) const
{
	return occupation;
}

void Machine::assign(Job& job) 
{
	occupation += job.getLength();
	job.setMachine(this);
	jobs.push_back(job);
}

vector<Job> Machine::getJobs(void) const
{
	return jobs;
}

