#include "philosopher.h"
#include <utils.h>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>
#include <vector>
#include "utils.h"


using namespace std;


Philosopher::Philosopher(int _number, std::mutex &_leftFork, std::mutex &_rightFork) : leftFork(_leftFork), rightFork(_rightFork)
{
    number = _number;
}

Philosopher::~Philosopher()
{
}

void Philosopher::getForks()
{
    println("Philosopher ", to_string(number), " attempts to get left fork");
    leftFork.lock();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    println("Philosopher ", to_string(number), " got left fork. Now he wants the right one...");
    
    if (!rightFork.try_lock())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        leftFork.unlock();
        println("Philosopher ", to_string(number), " released left fork due to timeout getting the right one!");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        getForks();
    }
}

void Philosopher::releaseForks()
{
    leftFork.unlock();
    println("Philosopher ", to_string(number), " released left fork");

    rightFork.unlock();
    println("Philosopher ", to_string(number), " released right fork");
}

void Philosopher::eat()
{
    println("Philosopher ", to_string(number), " is thinking...");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    getForks();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    println("Philosopher ", to_string(number), " finished eating");

    releaseForks();
}


