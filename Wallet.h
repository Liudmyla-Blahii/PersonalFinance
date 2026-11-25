#pragma once
#include "Account.h"

class Wallet : public Account
{
public:
    Wallet(const string& name, double balance)
        : Account(name, balance)
    {
    }

    void print() const override
    {
        cout << "Гаманець: " << name
            << " | Баланс: " << balance << " грн" << endl;
    }
};
