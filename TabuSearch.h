#include "systemc.h"

SC_MODULE(TabuSearch) {
	static const int TASK_NUM = 9;							// global tasks number
	static const int FINAL_STEP = 90;						// declare final steps for algorithm limitation
	static const int SOLUTION_NUMBER = 512;					// number of random solutions
	static const int MAX_TABU_SIZE = 10;					// maximum length of tabu list size

	sc_out<sc_bv<9>> output;
	sc_out<bool> output_generate;

	int best_value, step;
	std::vector<sc_bv<TASK_NUM>> neigbors;
	std::vector<sc_bv<TASK_NUM>> tabu_list;
	sc_bv<TASK_NUM> solutions[SOLUTION_NUMBER];
	sc_bv<TASK_NUM> best_solution;
	

	void search();
	int check_solution(sc_bv<TASK_NUM> solution);
	void make_solutions();	
	bool check_final();	
	void make_output();		
	void find_neighbors(sc_bv<TASK_NUM> solution);


	SC_CTOR(TabuSearch) {
		SC_THREAD(search);
	}
};