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
                
                if (errno) {
                    cerr << "starting charout failed: " << strerror(errno) << endl;
                    exit(1);  
                }
            }else {
                cout << "ABA_LETTER_A not set" << endl;
                exit(1);  
            }
        exit(0);   
        }
        else {
            pid_t pid2{fork()};
            if (pid2 == 0) {
                if (aba_letter_b) {
                    execl("./charout", "./charout", aba_letter_b, 0);
                    if (errno) {
                        cerr << "starting charout failed: " << strerror(errno) << endl;
                        exit(1);  
                    }
                    
                }else {
                    cout << "ABA_LETTER_B not set" << endl;
                    exit(1);  
                }  
                exit(0);  
            }

            cout << "waiting for 3 seconds" << endl;
            std::chrono::milliseconds sleeptime(3000);
            std::this_thread::sleep_for(sleeptime);

            cout << "\n" << flush;

            cout << "killing both subprocesses with pids " << pid1 << " and " << pid2 << endl;
            cout << "waiting for both subprocesses to be dead" << endl;

            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);

            int status1;
            int status2;
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);

            cout << "subprocess " << pid1 <<" exited with "<< WEXITSTATUS(status1) << endl;
            cout << "subprocess " << pid2 <<" exited with "<< WEXITSTATUS(status2) << endl;

            exit(EXIT_SUCCESS);
        }
}