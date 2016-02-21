//
// Created by yshen on 21/02/16.
//

#include <iostream>
#include <string>
#include "mem_block_bench.h"
#include "mbw.h"

using namespace std;

const static string VERSION = "1.0";
const static int DEFAULT_BLOCK_SIZE = 4096;

static void usage(void) {
    cout << "mbw memory benchmark v" << VERSION << ", https://github.com/raas/mbw" << endl;
    cout << "Usage: mbw [options] array_size_in_MiB" << endl;
    cout << "Options:" << endl;
    cout << "    -n: number of runs per test" << endl;
    cout << "    -a: Don't display average" << endl;
    cout << "    -t" << static_cast<int>(mbw_type::MEM_COPY) << ": memcpy test" << endl;
    cout << "    -t" << static_cast<int>(mbw_type::MEM_DUMB) << ": dumb (b[i]=a[i] style) test" << endl;
    cout << "    -t" << static_cast<int>(mbw_type::MEM_BLK_COPY) << ": memcpy test with fixed block size" << endl;
    cout << "    -t" << static_cast<int>(mbw_type::MEM_ARCH_COPY) << ": memcpy using architecture-dependant assembly" << endl;
    cout << "    -b <size>: block size in bytes for -t2 (default: " << DEFAULT_BLOCK_SIZE << endl;
    cout << "    -T <num_threads>: running the benchmark concurrently in multiple threads" << endl;
    cout << "    -q: quiet (print statistics only)" << endl;
    cout << "(will then use two arrays, watch out for swapping)" << endl;
    cout << "'Bandwidth' is amount of data copied over the time this operation took." << endl;
    cout << "The default is to run all tests available." << endl;

}

int main(int argc, char **argv)
{
    usage();
    mem_block_bench<10> mbb(1000, 1024, 1024 * 1024 * 4);
    mbb.run();
    mbb.finish();
    mbb.print(std::cout);
    return 0;
}
