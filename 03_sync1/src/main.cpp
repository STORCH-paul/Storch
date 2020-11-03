#include <iostream>

#include "account.h"

using namespace std;

int main() {
  account a{0};

  a.deposit(15);
  a.withdraw(6);
  cout << a.withdraw(10) << endl;
  cout << a.get_balance() << endl;
}