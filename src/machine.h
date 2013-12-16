#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include "job.h" 

class Machine
{
	public:
		Machine(const int id);
		int getId(void) const;
		int getOccupation(void) const;
		void assign(Job& job);
		std::vector<Job> getJobs(void) const;

	private:
		int id;
		int occupation;
		std::vector<Job> jobs;
};

#endif
