#include "TabuSearch.h"

/*
* start Tabu search algorithm
*/
void TabuSearch::search() {
	srand(time(0));
	make_solutions();																	// make random solutions

	best_value = check_solution(solutions[0]);
	best_solution = solutions[0];
	sc_bv<TASK_NUM> next_candidate = solutions[0];
	step = 1;
	output_generate = false;

	tabu_list.push_back(0);																// add solution[0] into tabu list

	while (true) {
		find_neighbors(next_candidate);													// find neighbors of desired solution
		next_candidate = neigbors[0];

		for (sc_bv<TASK_NUM> neighbor : neigbors) {										// find best solution between all neighbors
			if (check_solution(neighbor) > check_solution(next_candidate) and 
				std::find(tabu_list.begin(), tabu_list.end(), neighbor) == tabu_list.end()) {
				next_candidate = neighbor;
			}
		}

		if (check_solution(next_candidate) > check_solution(best_solution)) {			// compare value of candidate solution with best solution
			best_solution = next_candidate;
		}

		tabu_list.push_back(next_candidate);											// check tabu list size
		if (tabu_list.size() > MAX_TABU_SIZE) {
			tabu_list.erase(tabu_list.begin());
		}

		step += 1;

		if (check_final()) {															// check for algorithm finish condition
			make_output();
			wait(5, SC_NS);
			sc_stop();
			break;
		}
	}
}

/*
* find all neighbors of desired solution
*/
void TabuSearch::find_neighbors(sc_bv<TASK_NUM> solution) {
	neigbors.clear();
	for (int i = 0; i < TASK_NUM; i++) {
		if (solution[i] == 1) {
			if (i > 1) {
				sc_bv<TASK_NUM> previous = solution;
				previous[i - 1] = 1;

				sc_bv<TASK_NUM> both = solution;
				both[i - 1] = 1;
				both[i + 1] = 1;

				neigbors.push_back(previous);
				neigbors.push_back(both);
			}
			sc_bv<TASK_NUM> next = solution;
			next[i + 1] = 1;
			neigbors.push_back(next);
		}
	}
}

/*
* make random solutions
*/
void TabuSearch::make_solutions() {
	for (int i = 0; i < SOLUTION_NUMBER; i++) {
		for (int j = 0; j < TASK_NUM; j++) {
			solutions[i][j] = rand() % 2;
		}
	}
}

/*
* store output
*/
void TabuSearch::make_output() {
	output = best_solution;
	output_generate = true;
}

/*
* check for algorithm finish
*/
bool TabuSearch::check_final() {
	if (step == FINAL_STEP) {
		return true;
	}
	else {
		return false;
	}
}

/*
* calculate value of desired solution
*/
int TabuSearch::check_solution(sc_bv<TASK_NUM> solution) {
	int prices[TASK_NUM] = {6, 5, 8, 5, 4, 7, 3, 6, 8};
	int weights[TASK_NUM] = {2, 3, 6, 7, 5, 9, 3, 4, 5};

	int price = 0;
	int weight = 0;
	int limitation = 20;

	for (int index = 0; index < TASK_NUM; index++) {
		if (solution[index] == 1) {
			price += prices[index];
			weight += weights[index];
		}
	}
	return weight > limitation ? -1 : price;
}