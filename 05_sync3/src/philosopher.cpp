#include "philosopher.h"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>


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
    ostringstream buf;
    buf << "Philosopher " << to_string(number) << " attempts to get left fork" << endl;
    cout << buf.str() << flush;
    buf.str("");
    leftFork.lock();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    buf << "Philosopher " << to_string(number) << " got left fork. Now he wants the right one..." << endl;
    cout << buf.str() << flush;
    buf.str("");
    if (!rightFork.try_lock())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        leftFork.unlock();
        buf << "Philosopher " << to_string(number) << " released left fork due to timeout getting the right one!" << endl;
        cout << buf.str() << flush;
        buf.str("");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        getForks();
    }
}

void Philosopher::releaseForks()
{
    ostringstream buf;
    leftFork.unlock();
    buf << "Philosopher " << to_string(number) << " released left fork" << endl;
    cout << buf.str() << flush;
    buf.str("");

    rightFork.unlock();
    buf << "Philosopher " << to_string(number) << " released right fork" << endl;
    cout << buf.str() << flush;
    buf.str("");
}

void Philosopher::eat()
{
    ostringstream buf;
    buf << string{"Philosopher "} << to_string(number) << string{" is thinking..."} << endl;
    cout << buf.str() << flush;
    buf.str("");
    std::this_thread::sleep_for(std::chrono::seconds(1));

    getForks();

    std::this_thread::sleep_for(std::chrono::seconds(2));
    buf << "Philosopher " << to_string(number) << " finished eating" << endl;
    cout << buf.str() << flush;
    buf.str("");

    releaseForks();
}
