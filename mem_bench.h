//
// Created by yshen on 21/02/16.
//

#ifndef MBW_MEM_BENCH_H
#define MBW_MEM_BENCH_H

#include <string>

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iomanip>
#include "barrier.h"

using namespace std;

template<int N>
class mem_bench {
    using duration_t = chrono::duration<double, std::micro>;

protected:
    int                     times;
    size_t                  copy_size;
    string                  name;
    duration_t              duration_us[N];
    double                  bw[N];

    static thread_local int tid;

    bool go[N];
    std::thread *thread[N];
    std::mutex mutex[N];
    std::condition_variable cv[N];
    sync::barrier<N> barrier;

    void do_bench_wrapper(int id);

public:
    mem_bench(int t, string n, size_t cs);
    void run(void);
    virtual void finish(void);
    virtual void run_bench() = 0;
    virtual ostream& print(ostream &out);
    virtual ~mem_bench();
};



template<int N>
mem_bench<N>::mem_bench(int t, string n, size_t cs)
        : times {t}, name {n}, copy_size {cs},
          go {false}
{
    for (int i = 0; i < N; i++) {
        thread[i] = new std::thread([this](int id) { mem_bench<N>::do_bench_wrapper(id); }, i);
    }

}

template<int N>
ostream& mem_bench<N>::print(ostream &out) {
    double total_size = copy_size * times * 2;
    double total = 0;
    for (int i = 0; i < N; i++) {
        double mega_bytes_per_second = total_size / duration_us[i].count();
        bw[i] = mega_bytes_per_second;
        total += bw[i];
        out << "Copied (MB): " << std::fixed << total_size / 1000 / 1000 << endl;
        out << "Seconds: " << std::fixed << duration_us[i].count() / 1000 / 1000 << endl;
        out << "MB/S: " << std::fixed << mega_bytes_per_second << endl;
    }
    out << "Total MB/S: " << std::fixed << total << endl;
    return out;
}

template<int N>
void mem_bench<N>::do_bench_wrapper(int id) {
    this->tid = id;
    pthread_t native_thread = thread[id]->native_handle();

    while (true) {
        std::unique_lock<std::mutex> lock(mutex[id]);
        if (go[id]) {
            break;
        }
        cv[id].wait(lock);
    }

    barrier.wait();
    this->run_bench();
}

template<int N>
void mem_bench<N>::run(void) {
    for (int i = 0; i < N; i++) {
        std::unique_lock<std::mutex> lock(mutex[i]);
        go[i] = true;
        cv[i].notify_all();
    }
}

template<int N>
void mem_bench<N>::finish(void)
{
    for (int i = 0; i < N; i++) {
        if (thread[i]) thread[i]->join();
    }
}

template<int N>
mem_bench<N>::~mem_bench()
{
    for (int i = 0; i < N; i++)
        if (thread[i]) delete thread[i];
}

template<int N>
thread_local int mem_bench<N>::tid = 0;

#endif //MBW_MEM_BENCH_H
