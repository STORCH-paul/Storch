#include "work_queue.h"

WorkQueue::WorkQueue(){

}

WorkQueue::~WorkQueue(){
}

void WorkQueue::push(WorkPacket workPacket){
    std::unique_lock<std::mutex> lock(mx);

    queue.push(workPacket);
    notEmptyCv.notify_one();
}

WorkPacket WorkQueue::pop(){
    std::unique_lock<std::mutex> lock(mx);
    notEmptyCv.wait(lock, [this] { return queue.size(); });

    WorkPacket ret{queue.front()};
    queue.pop();

    return ret;
}