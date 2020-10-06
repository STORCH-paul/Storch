#include <iostream>
#include <thread>
#include <sys/wait.h>
#include <random>
#include <iomanip>
#include <string>
#include <cerrno>


using namespace std;

class Car {
    private:
        double total_time{0};
        string name;
        int laps{10};
    public:
        Car(string _name);
        ~Car();
        void operator()();
        double get_total_time();
        void setlaps(int _laps);
};

Car::Car(string _name) {
    name = _name;
}

void Car::setlaps(int _laps) {
    laps = _laps;
}

Car::~Car() {
}

void Car::operator()() {
    ostringstream buf;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};

    int count{1};
    
    while (count <= laps) {
        double round_time{dis(gen)};
        this_thread::sleep_for(chrono::milliseconds{u_int((round_time * 1000))});
        buf << to_string(count) << " " << name << " " << setprecision(3) << round_time << "s\n";
        cout << buf.str() << flush;
        total_time += round_time;
        count++;
        buf.str("");
    }
}

double Car::get_total_time() {
    return total_time;
}

void dacia_logan_mcv(){
    int count{1};
    while (true) {
        this_thread::sleep_for(1s);
        cout << count << " Dacia Logan MCV" << endl;
        count++;
    }
}

void help() {
    cout << "Usage: contest [-h | --help | LAPS]" << endl;
}

void error(string msg="") {
    if(msg != ""){
        cout << msg << endl;
        cout << "Run with --help for more information." << endl;
    }
    quick_exit(1);
}

int main(int argc, char* argv[]) {
    Car dacia_logan("Dacia Logan");
    Car honda_civic("Honda Civic");

    int laps{0};
    if(argc != 0){
        if (string(argv[1]) == "-h" || string(argv[1]) == "--help" ){
            help();
        }else {
            try{
                laps = stoi(argv[1]);
            }catch (const invalid_argument& e){
                error("Could not convert: "  + string(argv[1]));
            }
            
            if(laps < 1 || laps >= 16){
                error("Out of range (1 <= LAP'S < 16): " + string(argv[1]));
            }else {
                    dacia_logan.setlaps(laps);
                    honda_civic.setlaps(laps);    

                    thread t1{&Car::operator(), ref(dacia_logan)};
                    thread t2{&Car::operator(), ref(honda_civic)};

                    t1.join();
                    t2.join();
                    if(dacia_logan.get_total_time() < honda_civic.get_total_time()) {
                        cout << "Gewinner Dacia Logan: " << dacia_logan.get_total_time() << endl;
                        cout << "Loser Honda Civic: " << honda_civic.get_total_time() << endl;
                    }else {
                        cout << "Gewinner Honda Civic: " << honda_civic.get_total_time() << endl;
                        cout << "Loser Dacia Logan: " << dacia_logan.get_total_time() << endl;
                    }
            }
        }
    }

    return 0;
}
