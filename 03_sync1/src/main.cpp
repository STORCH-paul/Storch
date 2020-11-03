#include <iostream>
#include <thread>

#include "CLI11.hpp"
#include "account.h"

using namespace std;

int main(int argc, char *argv[]) {
  CLI::App app("Account app");
  int balance{0};
  app.add_option("balance", balance, "Initial balance")->required();
  int deposits{5};
  app.add_option("-d,--deposits", deposits, "Count of deposits", true);
  CLI11_PARSE(app, argc, argv);

  account a{balance};

  // Point 1
  //   a.deposit(15);
  //   a.withdraw(6);
  //   cout << a.withdraw(10) << endl;
  //   cout << a.get_balance() << endl;

  // Point 2
  //thread t1{[&](){a.withdraw(1);}};
  //thread t2{[&](){a.withdraw(1);}};
  
  //t1.join();
  //t2.join();

  // Point 3
  depositer d1{&a, deposits};
  depositer d2{&a, deposits};

  thread t1{d1};
  thread t2{d2};

  t1.join();
  t2.join();

  cout << a.get_balance() << endl;

}