//
// Created by yshen on 21/02/16.
//

#ifndef MBW_MEM_BLOCK_BENCH_H
#define MBW_MEM_BLOCK_BENCH_H

#include "mem_bench.h"
#include <string>
#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

template<int N>
class mem_block_bench : public mem_bench<N> {

protected:
    size_t  blk_size;
    char *src_buf;
    char *dest_buf;

public:
    mem_block_bench(int t, size_t bs, size_t cs);
    virtual void run_bench(void);
    virtual ~mem_block_bench();
};


template<int N>
mem_block_bench<N>::mem_block_bench(int t, size_t bs, size_t cs)
        : mem_bench<N>(t, "block", cs), blk_size {bs}
{
    this->src_buf = new char[this->copy_size];
    this->dest_buf = new char[this->copy_size];

    /* touch the buffers to make sure they are in memory */
    bzero(src_buf, this->copy_size);
    bzero(dest_buf,this->copy_size);
}

template<int N>
void mem_block_bench<N>::run_bench(void) {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; this->times > i; i++) {
        memcpy(dest_buf, src_buf, this->copy_size);
    }
    auto end = chrono::high_resolution_clock::now();
    this->duration_us[this->tid] = end - start;
    cout << this->duration_us[this->tid].count() << endl;
}

template<int N>
mem_block_bench<N>::~mem_block_bench() {
    if (src_buf) delete[] src_buf;
    if (dest_buf) delete[] dest_buf;
}
#endif //MBW_MEM_BLOCK_BENCH_H
