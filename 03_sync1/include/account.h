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
