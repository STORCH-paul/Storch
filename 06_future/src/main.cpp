#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop
#include <iostream>
#include <future>
#include <vector>
#include <string>
#include <thread>
#include "calc_factors.h"
#include "CLI11.hpp"

using namespace std;

string check_callable(const string& numbers){
    size_t check{numbers.find_first_not_of("0123456789")};
    if(check == string::npos){
        return "";
    }
    else{
        return string(numbers) + " contains not numeric character";
    }  
}

void factoring(vector<string>& numbers, vector<shared_future<vector<InfInt>>>& futs, bool& sync){
    for (auto num : numbers)
    {
        InfInt number = num;
        if(sync){
            futs.push_back(async(launch::async, get_factors, InfInt(number)));
        }else{
            futs.push_back(async(get_factors, InfInt(number)));
        }
    }
}

void checkFactors(vector<string>& numbers, vector<shared_future<vector<InfInt>>>& futs)
{
    for (unsigned int i{}; i < futs.size(); i++){
        InfInt prod = 1;
        futs.at(i).wait();
        for (auto number : futs.at(i).get()){
            prod *= number;
        }
        if (prod != InfInt(numbers.at(i))){
            cerr << "Factoring FAILED for: " << numbers.at(i) << endl;
        }
    }
}

int main(int argc, char *argv[]){
    CLI::App app("Factor numbers");
    vector<string> numbers{};
    bool async{false};
    app.add_option("number", numbers, "numbers to factor")->required()->check(check_callable);
    app.add_flag("-a,--async", async, "async");
    CLI11_PARSE(app, argc, argv);
    vector<shared_future<vector<InfInt>>> futs{};
    auto start = chrono::system_clock::now();
    thread factorThread{factoring, ref(numbers), ref(futs), ref(async)};
    factorThread.join();
    thread checkThread{checkFactors, ref(numbers), ref(futs)};
    checkThread.join();
    for (unsigned int i{}; i < futs.size(); i++){
        cout << numbers.at(i) << ": ";
        for (auto primes : futs.at(i).get())
        {
            cout << primes.toString() << " ";
        }
        cout << endl;
    }
    auto duration = chrono::duration_cast<chrono::milliseconds>
    (std::chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;
}