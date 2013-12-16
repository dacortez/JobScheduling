/*******************************************************************************
 * MAC0325 - Otimização Combinatória
 *
 * Projeto: Escalonamento de Tarefas
 * Aluno: Daniel Augusto Cortez (dacortez79@gmail.com)
 *
 * Data: 29/11/2013
 ******************************************************************************/

#include <cmath>
#include <iostream>
#include <string>
#include "cplex_scheduler.h"

using namespace std;

CplexScheduler::CplexScheduler(vector<Machine> machines, vector<Job> jobs) 
	: Scheduler(machines, jobs)
{
	m = machines.size();
	n = jobs.size();
}

// Resolve o problema do escalonamento utilizando o modelo de programção
// linear construído no CPLEX. Retorna true no sucesso, false caso contrário.
bool CplexScheduler::schedule(void)
{
	IloEnv env;

	try {
		IloModel model(env);

		typedef IloArray<IloBoolVarArray> BoolVarMatrix;
		BoolVarMatrix x(env, n);
		for (int i = 0; i < n; i++)
			x[i] = IloBoolVarArray(env, m);

		char buf[128];
		for(int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				sprintf(buf, "x%d,%d", i, j);
				x[i][j].setName(buf);
			}

		IloIntVar z(env, "z");	
		model.add(IloMinimize(env, z));
		
		for(int i = 0; i < n; i++) {	
			IloExpr r(env);
			for (int j = 0; j < m; j++)
				r += x[i][j];
			model.add(r == 1);					
		}

		for(int j = 0; j < m; j++) {	
			IloExpr r(env);
			for (int i = 0; i < n; i++)
				r += jobs[i].getLength() * x[i][j];
			model.add(r <= z);					
		}

		IloCplex mycplex(model);
		mycplex.setParam(IloCplex::EpGap, 0.0);
		mycplex.setParam(IloCplex::TiLim, 180.0);
		//mycplex.exportModel("sched.lp");

		if (mycplex.solve()) {
			mycplex.out() << "Solution Status is " << mycplex.getStatus() << endl;
			mycplex.out() << "The objective value is " << mycplex.getObjValue() << endl;		
			for (int j = 0; j < m; j++) {
				for (int i = 0; i < n; i++)
					if ((int) (mycplex.getValue(x[i][j]) + 0.5))
						machines[j].assign(jobs[i]);
					if (machines[j].getOccupation() > max)
						max = machines[j].getOccupation();
			}
		}
  }
  catch (IloException& e) {
 		cerr << "Concert exception caught: " << e << endl;
 		env.end();
 		return false;
  }
  catch (...) {
  	cerr << "Unknown exception caught" << endl;
  	env.end();
  	return false;
  }
  env.end();
	return true;
}

void CplexScheduler::printSchedule(void) const
{
	cout << "---------------------------------------------------" << endl;
	cout << "Escalonamento exato CPLEX:" << endl;
	Scheduler::printSchedule();
}
