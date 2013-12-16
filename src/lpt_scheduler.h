#ifndef LPT_SCHEDULER_H
#define LPT_SCHEDULER_H

#include <queue>
#include "scheduler.h"

class LptScheduler: public Scheduler
{
	public:
		LptScheduler(std::vector<Machine> machines, std::vector<Job> jobs);
		bool schedule(void);
		void printSchedule(void) const;
	
	private:
		struct machineComparator {
			bool operator() (const Machine *m1, const Machine *m2) const;
		};
		struct jobComparator {
			bool operator() (const Job j1, const Job j2) const;
		} JobComparator;
		std::priority_queue<Machine*, std::vector<Machine*>, machineComparator> pq;
};

#endif
