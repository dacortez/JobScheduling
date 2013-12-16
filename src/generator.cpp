#include <cstdlib>
#include <iostream>
#include <time.h>
#include "generator.h"

Generator::Generator(int totalMachines, int totalJobs) 
{ 
	this->totalMachines = totalMachines;
	this->totalJobs = totalJobs;
	srand (time(NULL));
}

void Generator::generate(int min, int max)
{
	generateMachines();
	generateJobs(min, max);
}

void Generator::generateMachines() 
{
	for (int i = 0; i < totalMachines; i++) {
		Machine machine(i);
		machines.push_back(machine);
	}
}

void Generator::generateJobs(int min, int max)
{
	for (int i = 0; i < totalJobs; i++) {
		int length = min + rand() % (max - min + 1);
		Job job(i, length);
		jobs.push_back(job);
	}
}

vector<Job> Generator::getJobs(void) const
{
	return jobs;
}

vector<Machine> Generator::getMachines(void) const
{
	return machines;
}

