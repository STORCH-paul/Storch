#include <iostream>
#include <sys/wait.h>
#include <cerrno>
#include <thread>
#include "work_packet.h"
#include "work_queue.h"

using namespace std;

void loadsim(WorkQueue &queue){
    int i{0};
    while(true){
        this_thread::sleep_for(500ms);
        queue.push(WorkPacket{i});
        cout << "B: Submitted work packet " << i << endl;
        i++;
    }
}

int main(){
    WorkQueue queue{};
    loadsim(queue);
}