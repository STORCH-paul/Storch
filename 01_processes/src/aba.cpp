#include <iostream>
#include <thread>
#include <unistd.h>
#include <csignal>
#include <sys/wait.h>
#include <cstring>


using namespace std;


int main() {

    pid_t pid1{fork()};
        if (pid1 == 0)
        {
            execl("./charout", "./charout", "A", 0);
        }
        else
        {
            pid_t pid2{fork()};
            if (pid2 == 0)
            {
                execl("./charout", "./charout", "B", 0);
            }

            std::chrono::milliseconds sleeptime(3000);
            std::this_thread::sleep_for(sleeptime);

            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);
            exit(EXIT_SUCCESS);
        }
        sleep(100);
}