//
// Created by yshen on 21/02/16.
//

#ifndef MBW_MEM_DUMP_BENCH_H
#define MBW_MEM_DUMP_BENCH_H

#include "mem_bench.h"

template<int N>
class mem_dumb_bench : public mem_bench<N> {
public:
    mem_dumb_bench(int t, size_t cs);
    virtual void run_bench(void);
    virtual ~mem_dumb_bench();
};


template<int N>
mem_dumb_bench<N>::mem_dumb_bench(int t, size_t cs) : mem_bench<N>(t, "dumb", cs) {

}

template<int N>
mem_dumb_bench<N>::~mem_dumb_bench() {

}

template<int N>
void mem_dumb_bench<N>::run_bench(void) {

}
#endif //MBW_MEM_DUMP_BENCH_H
