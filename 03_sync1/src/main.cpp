#include <iostream>
#include <thread>

#include "account.h"

using namespace std;

int main() {
  account a{1};

  // Point 1
  //   a.deposit(15);
  //   a.withdraw(6);
  //   cout << a.withdraw(10) << endl;
  //   cout << a.get_balance() << endl;

  thread t1{[&](){a.withdraw(1);}};
  thread t2{[&](){a.withdraw(1);}};
  
  t1.join();
  t2.join();
  
  cout << a.get_balance() << endl;
}