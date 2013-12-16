/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "job.h"
#include "machine.h"

class Scheduler
{
	public:
		Scheduler(std::vector<Machine> machines, std::vector<Job> jobs);
		virtual bool schedule(void) = 0;
		int getMaxOccupation(void) const;
		int getMachineOccupation(const int machineId) const;
		int getMachineId(const int jobId) const;
		virtual void printSchedule(void) const;

	protected:
		std::vector<Machine> machines;
		std::vector<Job> jobs;
		int max;
		void printMachines(void) const;
		void printJobs(void) const;
		void printOccupations(void) const;
};

#endif