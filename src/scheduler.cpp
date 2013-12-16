/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#include <iostream>
#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(vector<Machine> machines, vector<Job> jobs) 
{
	this->machines = machines;
	this->jobs = jobs;
	max = 0;
}

// Retorna a maior ocupação entre as máquinas (o makespan).
int Scheduler::getMaxOccupation(void) const
{
	return max;
}

// Retorna a ocupação da máquina de id machineId.
int Scheduler::getMachineOccupation(const int machineId) const
{
	for (int i = 0; i < machines.size(); i++)
		if (machines[i].getId() == machineId)
			return machines[i].getOccupation();
	return -1;
}
		
// Retorna o id da máquina que a tarefa de id jobId está escalonada.
int Scheduler::getMachineId(const int jobId) const
{
	for (int i = 0; i < jobs.size(); i++)
		if (jobs[i].getId() == jobId)
			return jobs[i].getMachine()->getId();
	return -1;
}

// Imprime o escolanamento das máquinas e a ocupação de cada máquina.
void Scheduler::printSchedule(void) const
{
	printMachines();
	printOccupations();
	cout << "- Occupação máxima = " << getMaxOccupation() << endl;
	cout << "---------------------------------------------------" << endl;
}

// Imprime cada máquina com a lista de tarefas processadas.
void Scheduler::printMachines(void) const
{
	for (int i = 0; i < machines.size(); i++) {
		int machineId = machines[i].getId();
		cout << "- Máquina " << machineId << ": ";
		vector<Job> machineJobs = machines[i].getJobs();
		for (int j = 0; j < machineJobs.size(); j++)
			cout << machineJobs[j].getId() << " ";
		cout << endl;
	}
}

// Imprime cada tarefa com a máquina de processamento associada.
void Scheduler::printJobs(void) const
{
	for (int i = 0; i < jobs.size(); i++) {
		int jobId = jobs[i].getId();
		cout << "- Tarefa " << jobId << ": " << getMachineId(jobId) << endl;	
	}
}

// Para cada máquina imprime a sua ocupação.
void Scheduler::printOccupations(void) const
{
	char buf[16];
	cout << "- Ocupação das máquinas: " << endl;
	for (int i = 0; i < machines.size(); i++) {
		int machineId = machines[i].getId();
		sprintf(buf, "%4d", machineId);
		cout << buf << ": " << getMachineOccupation(machineId) << endl;
	}	
}