#include <iostream>
#include <thread>
#include <unistd.h>
#include <csignal>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>


using namespace std;


int main() {
    const char* aba_letter_a{getenv("ABA_LETTER_A")};
    const char* aba_letter_b{getenv("ABA_LETTER_B")};

    pid_t pid1{fork()};
        if (pid1 == 0) {
            if (aba_letter_a) {
                execl("./charout", "./charout", aba_letter_a, 0);
            }else {
                cout << "ABA_LETTER_A not set" << endl;
            }   
        }
        else {
            pid_t pid2{fork()};
            if (pid2 == 0) {
                if (aba_letter_b) {
                    execl("./charout", "./charout", aba_letter_b, 0);
                }else {
                    cout << "ABA_LETTER_B not set" << endl;
                }    
            }

            std::chrono::milliseconds sleeptime(3000);
            std::this_thread::sleep_for(sleeptime);

            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);
            exit(EXIT_SUCCESS);
        }
        sleep(100);
}