//
// Created by yshen on 21/02/16.
//

#ifndef MBW_MEMCOPY_BENCH_H
#define MBW_MEMCOPY_BENCH_H

#include "mem_bench.h"

template <int N>
class memcopy_bench : public mem_bench<N> {
public:
    memcopy_bench(int n, size_t cs);
    virtual void run_bench(void);
    virtual ~memcopy_bench();
};


template<int N>
void memcopy_bench<N>::run_bench(void)
{
}

template<int N>
memcopy_bench<N>::~memcopy_bench()
{
}

template<int N>
memcopy_bench<N>::memcopy_bench(int n, size_t cs)
        : mem_bench<N>(n, "memcopy", cs)
{

}
#endif //MBW_MEMCOPY_BENCH_H
