//
// Created by yshen on 21/02/16.
//

#ifndef MBW_BARRIER_H
#define MBW_BARRIER_H

#include <atomic>
#include <iostream>

namespace sync {
    template <int N>
    class barrier {
        using flag_t = uint8_t;
    private:
        std::atomic<uint32_t> count;
        volatile flag_t global_flag;

    public:
        barrier() : count {0}, global_flag {0} {};
        void wait(void);
    };
};

template <int N>
void sync::barrier<N>::wait(void) {
    flag_t flag = global_flag;

    count++;
    if (count == N) {
        count = 0;
        global_flag = 1 - global_flag;
    }

    while (1) {
        if (flag != global_flag) {
            break;
        }
    }
}

#endif //MBW_BARRIER_H
