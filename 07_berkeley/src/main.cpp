#include <thread>
#include <iostream>

#include "clock.h"
#include "timeslave.h"
#include "timemaster.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char *argv[]){
    CLI::App app("Simulate the berkeley-algo");
    bool monotone{false};
    int delayS1{0};
    int delayS2{0};
    int rateS1{0};
    int rateS2{0};
    int rateM{0};
    app.add_flag("-m,--monotone", monotone, "set monotone mode");
    app.add_option("--latency1", delayS1, "latency to channel 1 (both directions)");
    app.add_option("--latency2", delayS2, "latency to channel 1 (both directions)");
    app.add_option("--deviation1", rateS1, "deviation of clock of slave 1");
    app.add_option("--deviation2", rateS2, "deviation of clock of slave 1");
    app.add_option("--deviationm", rateM, "deviation of clock of master");
    CLI11_PARSE(app, argc, argv);

    TimeMaster master{"Master", 0, 0, 5, monotone};
    TimeSlave slave1{"Slave1", 0, 0, 10, monotone};
    TimeSlave slave2{"Slave2", 0, 0, 15, monotone};

    slave1.get_channel()->set_latency(delayS1);
    slave2.get_channel()->set_latency(delayS2);

    master.set_clock_speed(rateM);
    slave1.set_clock_speed(rateS1);
    slave2.set_clock_speed(rateS2);

    master.set_channel1(slave1.get_channel());
    master.set_channel2(slave2.get_channel());

    thread clock_thread{std::ref(clock)};
    thread master_thread{std::ref(master)};
    thread slave1_thread{std::ref(slave1)};
    thread slave2_thread{std::ref(slave2)};

    clock_thread.join();
    master_thread.join();
    slave1_thread.join();
    slave2_thread.join();

    return EXIT_SUCCESS;
}