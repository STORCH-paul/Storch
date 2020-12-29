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

void factoring(vector<string>& numbers, vector<shared_future<vector<InfInt>>>& futs){
    for (auto num : numbers)
    {
        InfInt number = num;
        futs.push_back(async(launch::async, get_factors, InfInt(number)));
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
    app.add_option("number", numbers, "numbers to factor")->required()->check(check_callable);
    CLI11_PARSE(app, argc, argv);
    vector<shared_future<vector<InfInt>>> futs{};
    thread factorThread{factoring, ref(numbers), ref(futs)};
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
}