#include "systemc.h"

SC_MODULE(Monitor) {
    sc_in<sc_bv<9>> output;
    sc_in<bool> output_generate;

    void print_result();                                      // print output

    SC_CTOR(Monitor) {
        SC_THREAD(print_result);
        sensitive << output_generate;
    }
};