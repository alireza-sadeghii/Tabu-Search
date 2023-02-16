/*
* @Author : Alireza Sadeghi
* Hardware/Software Codesign
* Tabu Search
* 4012
*/


#include "systemc.h"
#include "TabuSearch.h"
#include "Monitor.h"

int sc_main(int argc, char* argv[]) {
    sc_core::sc_report_handler::set_actions("/IEEE_Std_1666/deprecated",
        sc_core::SC_DO_NOTHING);

    sc_signal<sc_bv<9>> t_output;
    sc_signal<bool> t_output_generate;
    
    TabuSearch ts("Tabu_Search");
    ts << t_output << t_output_generate;
    
    Monitor m("monitor");
    m << t_output << t_output_generate;
    
    sc_start();
	return(0);
}