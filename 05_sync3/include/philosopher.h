#pragma once

#include <mutex>
#include <vector>
#include <initializer_list>
#include <string>

class Philosopher
{
private:
  int number;
  std::mutex &leftFork;
  std::mutex &rightFork;
  int forkTimeout;
  void getForks();
  void releaseForks();

public:
  Philosopher(int _number, std::mutex &_leftFork, std::mutex &_rightFork);
  ~Philosopher();
  void eat();
};