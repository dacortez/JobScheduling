/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

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

// Resolve o problema do escalonamento utilizando a heurística LPT.
// Retorna true no sucesso, false caso contrário.
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

// Operador para ordenação das máquinas (por ocupação) na fila de prioridades.
inline bool LptScheduler::machineComparator::operator() (const Machine *m1, const Machine *m2) const
{ 
	return (m1->getOccupation() > m2->getOccupation()); 
}

// Operador para ordenação das tarefas (por duração, ordem decrescente).
inline bool LptScheduler::jobComparator::operator() (const Job j1, const Job j2) const
{ 
	return (j1.getId() < j2.getId()); 
}
