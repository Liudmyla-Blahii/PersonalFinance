#pragma once

#include "Account.h"

class Card : public Account

{

protected:

    string cardNumber;

public:

    Card(const string& name, const string& cardNumber, double balance)

        : Account(name, balance), cardNumber(cardNumber)

    {
    }

};

class DebitCard : public Card

{

public:

    DebitCard(const string& name, const string& number, double balance)

        : Card(name, number, balance)

    {
    }

    void print() const override

    {

        cout << "Дебетова картка: " << name
            << " | Баланс: " << balance << " грн" << endl;

    }

};

class CreditCard : public Card

{

private:

    double creditLimit;

public:

    CreditCard(const string& name, const string& number,

        double balance, double creditLimit)

        : Card(name, number, balance), creditLimit(creditLimit)

    {
    }

    bool withdraw(double amount) override

    {

        if (amount <= 0 || amount > balance + creditLimit)

            return false;

        balance -= amount;

        return true;

    }

    void print() const override

    {

        cout << "Кредитна картка: " << name
            << " | Баланс: " << balance
            << " грн | Кредитний ліміт: "
            << creditLimit << " грн" << endl;

    }

};


