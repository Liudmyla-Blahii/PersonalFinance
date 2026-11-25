#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Transaction
{
private:
    string accountName;
    string category;
    double amount;
    bool expense;
    time_t date;

public:
    Transaction(const string& accountName,
        const string& category,
        double amount,
        bool expense)
        : accountName(accountName),
        category(category),
        amount(amount),
        expense(expense),
        date(time(nullptr))
    {
    }

    string getAccountName() const { return accountName; }
    string getCategory() const { return category; }
    double getAmount() const { return amount; }
    bool isExpense() const { return expense; }
    time_t getDate() const { return date; }

    void print() const
    {
        cout << (expense ? "Витрата" : "Поповнення")
            << " | " << accountName
            << " | " << category
            << " | " << amount << " грн" << endl;
    }
};