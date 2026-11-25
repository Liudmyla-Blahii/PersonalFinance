#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account
{
protected:
    string name;
    double balance;

public:
    Account(const string& name, double balance)
        : name(name), balance(balance)
    {
    }

    virtual ~Account() = default;

    virtual void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
    }

    virtual bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    virtual void print() const
    {
        cout << name << ": " << balance << " грн" << endl;
    }

    double getBalance() const
    {
        return balance;
    }

    string getName() const
    {
        return name;
    }
};
