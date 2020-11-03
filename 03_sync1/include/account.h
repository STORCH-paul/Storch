#include <thread>
#include <mutex>

using namespace std;

class account
{
private:
  int balance{0};
  mutex balance_lock;

public:
  account(int balance);
  int get_balance();
  void deposit(int amount);
  bool withdraw(int amount);
};

class depositer
{
private:
  account* acc;
  int _deposits;

public:
  depositer(account* a, int deposits){
    acc = a;
    _deposits = deposits;
  }

  void operator()()
  {
    for (int i = 0; i < _deposits; i++)
    {
      this_thread::sleep_for(100ms * i);
      acc->deposit(1);
    }
  };
};