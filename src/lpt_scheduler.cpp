#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include "lpt_scheduler.h"

using namespace std;

LptScheduler::LptScheduler(vector<Machine> machines, vector<Job> jobs) 
	: Scheduler(machines, jobs)
{
}

bool LptScheduler::schedule(void)
{
	sort(jobs.begin(), jobs.end());
	for (int i = 0; i < machines.size(); i++)
		pq.push(&machines[i]);
	for (int i = 0; i < jobs.size(); i++) {
		Machine *machine = pq.top();
 		pq.pop();
		machine->assign(jobs[i]);
		pq.push(machine);
		if (machine->getOccupation() > max)
 			max = machine->getOccupation();
	}
	sort(jobs.begin(), jobs.end(), JobComparator);
	return true;
}

void LptScheduler::printSchedule(void) const
{
	cout << "---------------------------------------------------" << endl;
	cout << "Escalonamento heurística LPT:" << endl;
	Scheduler::printSchedule();
}

inline bool LptScheduler::machineComparator::operator() (const Machine *m1, const Machine *m2) const
{ 
	return (m1->getOccupation() > m2->getOccupation()); 
}

inline bool LptScheduler::jobComparator::operator() (const Job j1, const Job j2) const
{ 
	return (j1.getId() < j2.getId()); 
}
