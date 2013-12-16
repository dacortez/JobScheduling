/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include "job.h"
#include "machine.h"

using namespace std;

static void printJob(Job job);
static void printMachine(Machine machine);

class Generator
{
	public:
		Generator(int totalMachines, int totalJobs);
		void generate(int min, int max);
		vector<Job> getJobs(void) const;
		vector<Machine> getMachines(void) const;

	private:
		int totalMachines;
		int totalJobs;
		vector<Job> jobs;
		vector<Machine> machines;
		void generateMachines();
		void generateJobs(int min, int max);
};

#endif