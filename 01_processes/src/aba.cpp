#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if( pid == 0){
        while(true) {
            cout << "B" << flush;
            sleep(1);
        }
    }
    else if (pid > 0) {
        while(true) {
            cout << "A" << flush;
            sleep(1);
        }
    }
}