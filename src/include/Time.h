#ifndef ILARGIA_UTILS_H
#define ILARGIA_UTILS_H

#include <chrono>

namespace Ilargia {
    using Time = std::chrono::milliseconds;
    inline Time time_now() {
        auto timeT = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(timeT) ;
    }
}

#endif //ILARGIA_UTILS_H
