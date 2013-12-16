#include <iostream>
#include <vector>
#include <stdio.h>
#include "cplex_scheduler.h"
#include "generator.h"
#include "job.h"
#include "lpt_scheduler.h"
#include "machine.h"
#include "scheduler.h"

using namespace std;

void fileInput(char **argv);
void randomInput(char **argv);
void makeSchedules(const vector<Machine>& machines, const vector<Job>& jobs);
void printJobs(vector<Job> jobs);
void printJob(Job job);
void printMachines(vector<Machine> machines);
void printMachine(Machine machine);

int main(int argc, char **argv) 
{
	if (argc != 2 && argc != 5) {
		cout << "Uso: bin/projeto325 <arquivo_de_entrada>" << endl;
		cout << " ou: bin/projeto325 <número_de_máquinas> <número_de_tarefas> <min> <max>" << endl;
		return 0;
	}

	if (argc == 2) {
		fileInput(argv);
	}
	else if (argc == 5) {
		randomInput(argv);
	}

	return 0;
}

void fileInput(char** argv) {
	FILE *fp;
	if (!(fp = fopen(argv[1], "r"))) {
		cerr << "Erro ao abrir arquivo de entrada." << endl;
		return;
	}
	
	int totalMachines, totalJobs;
	fscanf(fp, "%d", &totalMachines);
	fscanf(fp, "%d", &totalJobs);

	if (totalMachines > 0 && totalJobs > 0) {
		vector<Machine> machines;
		vector<Job> jobs;
		for (int i = 0; i < totalMachines; i++) {
			Machine machine(i);
			machines.push_back(machine);
		}
		for (int i = 0; i < totalJobs; i++) {
			int length;
			fscanf(fp, "%d", &length);
			Job job(i, length);
			jobs.push_back(job);
		}
		fclose(fp);
		makeSchedules(machines, jobs);
	}
	else {
		cout << "Parâmentros inválidos." << endl;
	}
}

void randomInput(char **argv) {
	int totalMachines = atoi(argv[1]);
	int totalJobs = atoi(argv[2]);
	int min = atoi(argv[3]);
	int max = atoi(argv[4]);
	
	if (totalMachines > 0 && totalJobs > 0 && min >= 1 && max >= min) {
		Generator generator(totalMachines, totalJobs);
		generator.generate(min, max);
		makeSchedules(generator.getMachines(), generator.getJobs());
	}
	else {
		cout << "Parâmentros inválidos." << endl;
	}
}

void makeSchedules(const vector<Machine>& machines, const vector<Job>& jobs) 
{
	printMachines(machines);
	printJobs(jobs);
	
	Scheduler *scheduler;
	int maxh, maxc;

	scheduler = new LptScheduler(machines, jobs);
	if (scheduler->schedule()) {
		scheduler->printSchedule();
		maxh = scheduler->getMaxOccupation();
	}

	scheduler = new CplexScheduler(machines, jobs);
	if (scheduler->schedule()) {
		scheduler->printSchedule();
		maxc = scheduler->getMaxOccupation();
	}

	cout << "Razão (LPT/OPT) = " << (double) maxh / maxc << endl;
}

void printMachines(vector<Machine> machines)
{
	cout << "Lista de máquinas criadas:" << endl;
	for_each(machines.begin(), machines.end(), &printMachine);
}

void printMachine(Machine machine)
{
	cout << "- Máquina " << machine.getId() << ": " << machine.getOccupation() << endl;
}

void printJobs(vector<Job> jobs)
{
	cout << "Lista de tarefas geradas:" << endl;
	for_each(jobs.begin(), jobs.end(), &printJob);
}

void printJob(Job job)
{
	cout << "- Tarefa " << job.getId() << ": " << job.getLength() << endl;
}

