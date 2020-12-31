#pragma once

#ifndef SEMAPHOR_H
#define SEMAPHOR_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
  private:
    int size;
    std::condition_variable notEmpty;
    std::mutex mtx;
    

  public:
    Semaphore(){
      size = 0;
    };
    Semaphore(int _size){
      size = _size;
    };
    void acquire();
    void release();
    int avaliblePermits();
};

#endif