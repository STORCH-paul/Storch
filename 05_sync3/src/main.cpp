#include <iostream>
#include <thread>
#include <mutex>
#include "philosopher.h"

using namespace std;


int main()
{

    mutex g1;
    mutex g2;
    mutex g3;
    mutex g4;
    mutex g5;


    Philosopher p1{1, g1, g2};
    Philosopher p2{2, g2, g3};
    Philosopher p3{3, g3, g4};
    Philosopher p4{4, g4, g5};
    Philosopher p5{5, g5, g1};

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