#include <iostream>
#include <thread>
#include <mutex>
#include "semaphore.h"
#include "philosopher.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char *argv[]){
    CLI::App app("Dining philosophers simulation");
    bool nodeadlock{false};
    app.add_flag("-n,--nodeadlock", nodeadlock, "Queue Size");
    bool livelock{false};
    app.add_flag("-l,--livelock", livelock, "Count of deposits");

    //app.add_option("-d,--deposits", deposits, "Count of deposits", true);
    CLI11_PARSE(app, argc, argv);

    timed_mutex g1;
    timed_mutex g2;
    timed_mutex g3;
    timed_mutex g4;
    timed_mutex g5;

    Semaphore *semaphore = nullptr;
    int timeout = 9999999;

    if (nodeadlock == true)
    {
        semaphore = new Semaphore{4};
    }
    else if (livelock == true)
    {
        timeout = 3;
    }

    Philosopher p1{1, g1, g2, semaphore, timeout};
    Philosopher p2{2, g2, g3, semaphore, timeout};
    Philosopher p3{3, g3, g4, semaphore, timeout};
    Philosopher p4{4, g4, g5, semaphore, timeout};
    Philosopher p5{5, g5, g1, semaphore, timeout};

    std::thread t1{&Philosopher::eat, ref(p1)};
    std::thread t2{&Philosopher::eat, ref(p2)};
    std::thread t3{&Philosopher::eat, ref(p3)};
    std::thread t4{&Philosopher::eat, ref(p4)};
    std::thread t5{&Philosopher::eat, ref(p5)};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}