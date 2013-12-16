/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#ifndef JOB_H
#define JOB_H

class Machine;

class Job 
{
	public:
		Job(const int id, const int length);
		int getId(void) const;
		int getLength(void) const;
		Machine* getMachine(void) const; 
		void setMachine(Machine *machine);
		bool operator< (const Job& other) const;

	private:
		int id;
		int length;
		Machine *machine;
};

#endif