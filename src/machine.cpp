/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#include "machine.h"

using namespace std;

Machine::Machine(const int id) 
{ 
	this->id = id;
	occupation = 0;
}

int Machine::getId(void) const
{
	return id;
}

int Machine::getOccupation(void) const
{
	return occupation;
}

void Machine::assign(Job& job) 
{
	occupation += job.getLength();
	job.setMachine(this);
	jobs.push_back(job);
}

vector<Job> Machine::getJobs(void) const
{
	return jobs;
}

