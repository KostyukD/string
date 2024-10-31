#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

class Bankomat 
{
private:
    int id; 
    int currentSum; 
    int minWithdraw; 
    int maxWithdraw; 
    int denominations[10]; 

public:

    void initialize(int atmId, int minW, int maxW) 
    {
        id = atmId;
        minWithdraw = minW;
        maxWithdraw = maxW;
        currentSum = 0;
        for (int i = 0; i < 10; i++) 
        {
            denominations[i] = 0;
        }
    }


    void loadCash(int denom, int count) 
    {
        if (denom % 100 != 0 || denom < 100 || denom > 1000) 
        {
            throw invalid_argument("Invalid denomination");
        }
        int index = denom / 100 - 1;
        denominations[index] += count;
        currentSum += denom * count;
    }


    void withdrawCash(int amount) 
    {
        if (amount < minWithdraw || amount > maxWithdraw) 
        {
            throw invalid_argument("Amount out of allowed range");
        }
        if (amount > currentSum)
        {
            throw invalid_argument("Insufficient funds");
        }

        currentSum -= amount;
    }


    string toString() const 
    {
        stringstream ss;
        ss << "ATM ID: " << id << "\n";
        ss << "Current Sum: " << currentSum << "\n";
        ss << "Min Withdraw: " << minWithdraw << "\n";
        ss << "Max Withdraw: " << maxWithdraw << "\n";
        ss << "Denominations: \n";
        for (int i = 0; i < 10; i++)
        {
            if (denominations[i] > 0) 
            {
                ss << (i + 1) * 100 << ": " << denominations[i] << "\n";
            }
        }
        return ss.str();
    }
};

int main() 
{
    Bankomat atm;
    atm.initialize(1, 100, 10000);
    atm.loadCash(100, 10);
    atm.loadCash(500, 5);

    cout << atm.toString() << endl;

    try 
    {
        atm.withdrawCash(1500);
        cout << "Withdrawal successful!\n";
    }
    catch (const exception& e) 
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << atm.toString() << endl;

    return 0;
}
