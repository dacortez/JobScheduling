#ifndef CPLEX_SCHEDULER_H
#define CPLEX_SCHEDULER_H

#include <ilcplex/ilocplex.h>
#include "scheduler.h"
ILOSTLBEGIN

class CplexScheduler: public Scheduler
{
	public:
		CplexScheduler(std::vector<Machine> machines, std::vector<Job> jobs);
		bool schedule(void);
		void printSchedule(void) const;

	private:
		int m;
		int n;
};

#endif
