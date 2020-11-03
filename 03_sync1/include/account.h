using namespace std;

class account
{
private:
  int balance{0};

public:
  account(int balance);
  int get_balance();
  void deposit(int amount);
  bool withdraw(int amount);
};
