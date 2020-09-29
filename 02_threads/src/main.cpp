#include <iostream>
#include <thread>
#include <sys/wait.h>
#include <random>


using namespace std;

class Car {
    private:
        string name;
    public:
        Car(string _name);
        ~Car();
        void operator()();
};

Car::Car(string _name) {
    name = _name;
}

Car::~Car() {
}

void Car::operator()() {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_real_distribution<> dis{1, 10};

    int count{1};
    while (true) {
        cout << flush;
        double round_time{dis(gen)};
        this_thread::sleep_for(chrono::milliseconds{u_int((round_time * 1000))});
        cout << to_string(count) << " " << name << " " << round_time << "\n";
        count++;
    }
}

void dacia_logan_mcv(){
    int count{1};
    while (true) {
        this_thread::sleep_for(1s);
        cout << count << " Dacia Logan MCV" << endl;
        count++;
    }
}

int main() {
    
    Car dacia_logan("dacia_logan");
    Car honda_civic("honda_civic");

    thread t1{&Car::operator(), ref(dacia_logan)};
    thread t2{&Car::operator(), ref(honda_civic)};

    t1.join();
    t2.join();

    this_thread::sleep_for(100s);
    return 0;
}
