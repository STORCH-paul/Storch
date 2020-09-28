#include <iostream>
#include <thread>
#include <unistd.h>
#include <csignal>

using namespace std;


int main() {
    pid_t pid{fork()};

    if( pid == 0){
        while(true) {
            cout << "A" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    }
    else if (pid > 0) {
        for(int count{0}; count < 6; count++) {
            cout << "B" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        kill(pid, SIGKILL);
    }
}