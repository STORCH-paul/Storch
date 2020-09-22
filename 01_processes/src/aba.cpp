#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if( pid == 0){
        while(true) {
            cout << "B" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    }
    else if (pid > 0) {
        while(true) {
            cout << "A" << flush;
            std::chrono::milliseconds sleeptime(500);
            std::this_thread::sleep_for(sleeptime);
        }
    }
}