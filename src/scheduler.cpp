#include <iostream>
#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(vector<Machine> machines, vector<Job> jobs) 
{
	this->machines = machines;
	this->jobs = jobs;
	max = 0;
}

int Scheduler::getMaxOccupation(void) const
{
	return max;
}

int Scheduler::getMachineOccupation(const int machineId) const
{
	for (int i = 0; i < machines.size(); i++)
		if (machines[i].getId() == machineId)
			return machines[i].getOccupation();
	return -1;
}
		
int Scheduler::getMachineId(const int jobId) const
{
	for (int i = 0; i < jobs.size(); i++)
		if (jobs[i].getId() == jobId)
			return jobs[i].getMachine()->getId();
	return -1;
}

void Scheduler::printSchedule(void) const
{
	printMachines();
	printOccupations();
	cout << "- Occupação máxima = " << getMaxOccupation() << endl;
	cout << "---------------------------------------------------" << endl;
}

void Scheduler::printMachines(void) const
{
	for (int i = 0; i < machines.size(); i++) {
		int machineId = machines[i].getId();
		cout << "- Máquina " << machineId << ": ";
		vector<Job> machineJobs = machines[i].getJobs();
		for (int j = 0; j < machineJobs.size(); j++)
			cout << machineJobs[j].getId() << " ";
		cout << endl;
	}
}

void Scheduler::printJobs(void) const
{
	for (int i = 0; i < jobs.size(); i++) {
		int jobId = jobs[i].getId();
		cout << "- Tarefa " << jobId << ": " << getMachineId(jobId) << endl;	
	}
}

void Scheduler::printOccupations(void) const
{
	char buf[16];
	cout << "- Ocupação das máquinas: " << endl;
	for (int i = 0; i < machines.size(); i++) {
		int machineId = machines[i].getId();
		sprintf(buf, "%4d", machineId);
		cout << buf << ": " << getMachineOccupation(machineId) << endl;
	}	
}
