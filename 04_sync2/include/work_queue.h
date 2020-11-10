#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include "work_packet.h"

class WorkQueue
{
  private:
    std::queue<WorkPacket> queue;
    std::mutex mx;
    std::condition_variable notEmptyCv;
    std::condition_variable notFullCv;

  public:
    WorkQueue();
    ~WorkQueue();
    void push(WorkPacket workPacket);
    WorkPacket pop();
};