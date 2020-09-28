#include <iostream>
#include <thread>
#include <unistd.h>
#include <csignal>
#include <sys/wait.h>

using namespace std;


int main() {
    pid_t pid{fork()};

    if( pid == 0){
        for(int count{0}; count < 6; count++) {
            cout << "A" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        quick_exit(123);
    }
    else if (pid > 0) {
        for(int count{0}; count < 6; count++) {
            cout << "B" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
        int status;
        waitpid(pid, &status, 0);
        exit(EXIT_SUCCESS);
    }
}