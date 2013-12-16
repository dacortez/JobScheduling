/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#ifndef LPT_SCHEDULER_H
#define LPT_SCHEDULER_H

#include <queue>
#include "scheduler.h"

class LptScheduler: public Scheduler
{
	public:
		LptScheduler(vector<Machine> machines, vector<Job> jobs);
		bool schedule(void);
		void printSchedule(void) const;
	
	private:
		struct machineComparator {
    	bool operator() (const Machine *m1, const Machine *m2) const;
		};
		struct jobComparator {
    	bool operator() (const Job j1, const Job j2) const;
		} JobComparator;
		priority_queue<Machine*, vector<Machine*>, machineComparator> pq;
};

#endif