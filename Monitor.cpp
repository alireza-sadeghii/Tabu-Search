#include "Monitor.h"

void Monitor::print_result() {
    while (output_generate == false) {
        wait();
    }
    wait(3, SC_NS);
    cout << "The Optimize Solution is : " << output << endl;
}