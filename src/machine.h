/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#ifndef MACHINE_H
#define MACHINE_H

#include <vector>
#include "job.h" 

using namespace std;

class Machine
{
	public:
		Machine(const int id);
		int getId(void) const;
		int getOccupation(void) const;
		void assign(Job& job);
		vector<Job> getJobs(void) const;

	private:
		int id;
		int occupation;
		vector<Job> jobs;
};

#endif