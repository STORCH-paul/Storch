#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop
#include <iostream>
#include <future>
#include <vector>
#include <string>
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

int main(int argc, char *argv[]){
    CLI::App app("Factor numbers");
    vector<string> numbers{};
    app.add_option("number", numbers, "numbers to factor")->required()->check(check_callable);
    CLI11_PARSE(app, argc, argv);
    vector<future<vector<InfInt>>> futs{};
    for (auto num : numbers)
    {
        InfInt number = num;
        futs.push_back(async(launch::async, get_factors, InfInt(number)));
    }
    for (unsigned int i{}; i < futs.size(); i++){
        cout << numbers.at(i) << ": ";
        futs.at(i).wait();
        for (auto primes : futs.at(i).get())
        {
            cout << primes.toString() << " ";
        }
        cout << endl;
    }
}