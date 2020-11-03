#include <account.h>

using namespace std;

account::account(int init_balance)
{
  balance = init_balance;
}

int account::get_balance()
{
  return balance;
}

void account::deposit(int amount)
{
  balance += amount;
}

bool account::withdraw(int amount)
{

  int new_balance{balance - amount};

  if (new_balance < 0)
  {
    return false;
  }
  else
  {
    balance = new_balance;

    return true;
  }
}