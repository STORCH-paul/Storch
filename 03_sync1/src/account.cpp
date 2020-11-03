#include <thread>
#include <account.h>

using namespace std;

account::account(int init_balance)
{
  balance_lock.lock();
  balance = init_balance;
  balance_lock.unlock();
}

int account::get_balance()
{
  return balance;
}

void account::deposit(int amount)
{
  unique_lock<mutex> lock(balance_lock);
  balance += amount;
}

bool account::withdraw(int amount)
{
  lock_guard<mutex> lock(balance_lock);

  int new_balance{balance - amount};

  if (new_balance < 0)
  {
    return false;
  }
  else
  {
    this_thread::yield();
    balance = new_balance;

    return true;
  }
}