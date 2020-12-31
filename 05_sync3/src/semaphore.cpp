#include <condition_variable>
#include <mutex>
#include <iostream>
#include "semaphore.h"

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    notEmpty.wait(lock, [this] { return size > 0; });
    size -= 1;
}

void Semaphore::release() {
    std::unique_lock<std::mutex> lock(mtx);
    size += 1;
    notEmpty.notify_one();
}

int Semaphore::avaliblePermits() {
    return size;
}