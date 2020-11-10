#include <iostream>
#include <sys/wait.h>
#include <cerrno>
#include <thread>
#include <random>
#include <iomanip>
#include <string>
#include <unistd.h>

#include "work_packet.h"
#include "work_queue.h"

using namespace std;

void Boss(WorkQueue &queue){
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{0, 1};

    int i{0};
    while(true){
        buf << "B: Waiting to submit work packet " << i << endl;
        cout << buf.str() << flush;
        buf.str("");

        double duration{dis(gen)};
        this_thread::sleep_for(chrono::milliseconds{u_int((duration * 1000))});
        queue.push(WorkPacket{i});
        buf << "B: Submitted work packet " << i << "(" <<duration << "s)" << endl;
        cout << buf.str() << flush;
        buf.str("");
        i++;
    }
}

void worker(int id, WorkQueue &queue){
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};

    while(true){
        buf << "W" << to_string(id) << ": Want work packet " << endl;
        cout << buf.str() << flush;
        buf.str("");
        WorkPacket p{queue.pop()};
        buf << "W" << to_string(id) << ": Got work packet " << to_string(p.getId()) << endl;
        cout << buf.str() << flush;
        buf.str("");

        double duration{dis(gen)};
        this_thread::sleep_for(chrono::milliseconds{u_int((duration * 1000))});


        buf << "W" << to_string(id) << ": Processed work packet " << to_string(p.getId()) << endl;
        cout << buf.str() << flush;
        buf.str("");
    }
}

int main(){
    WorkQueue queue{};

    thread w1{worker, 1, ref(queue)};
    thread w2{worker, 2, ref(queue)};
    thread w3{worker, 3, ref(queue)};

    Boss(queue);

    w1.join();
    w2.join();

    return EXIT_SUCCESS;
}