#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <utility>
#include <fstream>
#include "Wallet.h"
#include "Card.h"
#include "Transaction.h"
using namespace std;

class FinanceManager
{
private:
    vector<shared_ptr<Account>> accounts;
    vector<Transaction> transactions;

public:
    void addWallet(const string& name, double balance)
    {
        accounts.push_back(make_shared<Wallet>(name, balance));
    }

    void addDebitCard(const string& name,
        const string& number, double balance)
    {
        accounts.push_back(
            make_shared<DebitCard>(name, number, balance));
    }

    void addCreditCard(const string& name,
        const string& number,
        double balance, double limit)
    {
        accounts.push_back(
            make_shared<CreditCard>(name, number, balance, limit));
    }

    void showAccounts() const
    {
        if (accounts.empty())
        {
            cout << "Рахунків поки немає" << endl;
            return;
        }

        for (int i = 0; i < accounts.size(); i++)
        {
            cout << i + 1 << ". ";
            accounts[i]->print();
        }
    }

    void depositMoney(int index, double amount)
    {
        if (index < 0 || index >= accounts.size())
        {
            cout << "Неправильний номер рахунку" << endl;
            return;
        }

        if (amount <= 0)
        {
            cout << "Сума має бути додатною" << endl;
            return;
        }

        accounts[index]->deposit(amount);

        transactions.push_back(
            Transaction(accounts[index]->getName(),
                "Поповнення", amount, false));

        cout << "Рахунок поповнено" << endl;
    }

    void addExpense(int index, double amount,
        const string& category)
    {
        if (index < 0 || index >= accounts.size())
        {
            cout << "Неправильний номер рахунку" << endl;
            return;
        }

        if (amount <= 0)
        {
            cout << "Сума має бути додатною" << endl;
            return;
        }

        if (accounts[index]->withdraw(amount))
        {
            transactions.push_back(
                Transaction(accounts[index]->getName(),
                    category, amount, true));

            cout << "Витрату додано" << endl;
        }
        else
        {
            cout << "Недостатньо коштів" << endl;
        }
    }

    void showTransactions() const
    {
        if (transactions.empty())
        {
            cout << "Операцій поки немає" << endl;
            return;
        }

        for (const Transaction& t : transactions)
        {
            t.print();
        }
    }

    void showReport(int period) const
    {
        time_t now = time(nullptr);
        double total = 0;

        cout << "\nЗВІТ ПРО ВИТРАТИ" << endl;

        for (const Transaction& t : transactions)
        {
            if (!t.isExpense())
                continue;

            double days = difftime(now, t.getDate()) / 86400;

            bool include = false;

            if (period == 1 && days < 1)
                include = true;
            else if (period == 2 && days < 7)
                include = true;
            else if (period == 3 && days < 30)
                include = true;

            if (include)
            {
                t.print();
                total += t.getAmount();
            }
        }

        cout << "Загальна сума витрат: "
            << total << " грн" << endl;
    }

    void showCategoryReport(int period) const

    {

        vector<pair<string, double>> categories;

        time_t now = time(nullptr);

        for (const Transaction& t : transactions)

        {

            if (!t.isExpense())

                continue;

            double days = difftime(now, t.getDate()) / 86400;

            bool include = false;

            if (period == 1 && days < 1)

                include = true;

            if (period == 2 && days < 7)

                include = true;

            if (period == 3 && days < 30)

                include = true;

            if (!include)

                continue;

            bool found = false;

            for (auto& category : categories)

            {

                if (category.first == t.getCategory())

                {

                    category.second += t.getAmount();

                    found = true;

                    break;

                }

            }

            if (!found)

            {

                categories.push_back(

                    { t.getCategory(), t.getAmount() });

            }

        }

        cout << "\nЗВІТ ЗА КАТЕГОРІЯМИ" << endl;

        if (categories.empty())

        {

            cout << "Витрат немає" << endl;

            return;

        }

        double total = 0;

        for (const auto& category : categories)

        {

            cout << category.first << " - "
                << category.second << " грн" << endl;

            total += category.second;

        }

        cout << "Загальна сума: "
            << total << " грн" << endl;

    }

    void showTopExpenses(int period) const
    {
        vector<Transaction> expenses;

        time_t now = time(nullptr);

        for (const Transaction& t : transactions)
        {
            if (!t.isExpense())
                continue;

            double days = difftime(now, t.getDate()) / 86400;

            if (period == 1 && days < 7)
                expenses.push_back(t);

            if (period == 2 && days < 30)
                expenses.push_back(t);
        }

        sort(expenses.begin(), expenses.end(),
            [](const Transaction& a, const Transaction& b)
            {
                return a.getAmount() > b.getAmount();
            });

        cout << "\nТОП-3 НАЙБІЛЬШИХ ВИТРАТ" << endl;

        if (expenses.empty())
        {
            cout << "Витрат немає" << endl;
            return;
        }

        int count = 0;

        for (const Transaction& t : expenses)
        {
            if (count == 3)
                break;

            t.print();
            count++;
        }
    }
    void showTopCategories(int period) const
    {
        vector<pair<string, double>> categories;

        time_t now = time(nullptr);

        for (const Transaction& t : transactions)
        {
            if (!t.isExpense())
                continue;

            double days = difftime(now, t.getDate()) / 86400;

            bool include = false;

            if (period == 1 && days < 7)
                include = true;

            if (period == 2 && days < 30)
                include = true;

            if (!include)
                continue;

            bool found = false;

            for (auto& category : categories)
            {
                if (category.first == t.getCategory())
                {
                    category.second += t.getAmount();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                categories.push_back(
                    { t.getCategory(), t.getAmount() });
            }
        }

        sort(categories.begin(), categories.end(),
            [](const pair<string, double>& a,
                const pair<string, double>& b)
            {
                return a.second > b.second;
            });

        cout << "\nТОП-3 КАТЕГОРІЙ ВИТРАТ" << endl;

        if (categories.empty())
        {
            cout << "Категорій немає" << endl;
            return;
        }

        for (int i = 0; i < categories.size() && i < 3; i++)
        {
            cout << i + 1 << ". "
                << categories[i].first << " - "
                << categories[i].second << " грн" << endl;
        }
    }

    void saveReportToFile() const

    {

        ofstream file("finance_report.txt");

        if (!file.is_open())

        {

            cout << "Не вдалося створити файл" << endl;

            return;

        }

        file << "ЗВІТ ПРО ОСОБИСТІ ФІНАНСИ\n";

        file << "============================\n\n";

        // Історія операцій

        file << "ІСТОРІЯ ОПЕРАЦІЙ:\n";

        for (const Transaction& t : transactions)

        {

            file << (t.isExpense() ? "Витрата" : "Поповнення")
                << " | " << t.getAccountName()
                << " | " << t.getCategory()
                << " | " << t.getAmount() << " грн\n";

        }

        // Загальна сума витрат

        double total = 0;

        for (const Transaction& t : transactions)

        {

            if (t.isExpense())

                total += t.getAmount();

        }

        file << "\nЗАГАЛЬНА СУМА ВИТРАТ:\n";

        file << total << " грн\n";

        // Звіти за періодами

        for (int period = 1; period <= 3; period++)

        {

            vector<pair<string, double>> categories;

            time_t now = time(nullptr);

            for (const Transaction& t : transactions)

            {

                if (!t.isExpense())

                    continue;

                double days = difftime(now, t.getDate()) / 86400;

                bool include = false;

                if (period == 1 && days < 1)

                    include = true;

                if (period == 2 && days < 7)

                    include = true;

                if (period == 3 && days < 30)

                    include = true;

                if (!include)

                    continue;

                bool found = false;

                for (auto& category : categories)

                {

                    if (category.first == t.getCategory())

                    {

                        category.second += t.getAmount();

                        found = true;

                        break;

                    }

                }

                if (!found)

                {

                    categories.push_back(

                        { t.getCategory(), t.getAmount() });

                }

            }

            file << "\nЗВІТ ЗА ";

            if (period == 1) file << "ДЕНЬ";

            if (period == 2) file << "ТИЖДЕНЬ";

            if (period == 3) file << "МІСЯЦЬ";

            file << " ПО КАТЕГОРІЯХ:\n";

            for (const auto& category : categories)

            {

                file << category.first << " - "
                    << category.second << " грн\n";

            }

        }

        // Рейтинги

        for (int period = 1; period <= 2; period++)

        {

            vector<Transaction> expenses;

            time_t now = time(nullptr);

            for (const Transaction& t : transactions)

            {

                if (!t.isExpense())

                    continue;

                double days = difftime(now, t.getDate()) / 86400;

                if ((period == 1 && days < 7) ||

                    (period == 2 && days < 30))

                {

                    expenses.push_back(t);

                }

            }

            sort(expenses.begin(), expenses.end(),

                [](const Transaction& a, const Transaction& b)

                {

                    return a.getAmount() > b.getAmount();

                });

            file << "\nТОП-3 ВИТРАТ ЗА ";

            if (period == 1) file << "ТИЖДЕНЬ:\n";

            else file << "МІСЯЦЬ:\n";

            for (int i = 0; i < expenses.size() && i < 3; i++)

            {

                file << i + 1 << ". "
                    << expenses[i].getCategory()
                    << " - " << expenses[i].getAmount()
                    << " грн\n";

            }

            file << "\nТОП-3 КАТЕГОРІЙ ЗА ";

            if (period == 1) file << "ТИЖДЕНЬ:\n";

            else file << "МІСЯЦЬ:\n";

            vector<pair<string, double>> categories;

            for (const Transaction& t : expenses)

            {

                bool found = false;

                for (auto& category : categories)

                {

                    if (category.first == t.getCategory())

                    {

                        category.second += t.getAmount();

                        found = true;

                        break;

                    }

                }

                if (!found)

                {

                    categories.push_back(

                        { t.getCategory(), t.getAmount() });

                }

            }

            sort(categories.begin(), categories.end(),

                [](const pair<string, double>& a,

                    const pair<string, double>& b)

                {

                    return a.second > b.second;

                });

            for (int i = 0; i < categories.size() && i < 3; i++)

            {

                file << i + 1 << ". "
                    << categories[i].first
                    << " - " << categories[i].second
                    << " грн\n";

            }

        }

        // Баланси рахунків

        file << "\nБАЛАНСИ РАХУНКІВ:\n";

        for (const auto& account : accounts)

        {

            file << account->getName()
                << " - " << account->getBalance()
                << " грн\n";

        }

        file.close();

        cout << "Звіт і рейтинги успішно збережено!" << endl;

    }
};