#include <iostream>
#include <windows.h>
#include <limits>
#include "FinanceManager.h"

using namespace std;

// Введення цілого числа
int readInt()
{
    int value;

    while (!(cin >> value))
    {
        cout << "Помилка! Введіть ціле число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return value;
}

// Введення додатного числа
double readDouble()
{
    double value;

    while (!(cin >> value) || value <= 0)
    {
        cout << "Помилка! Введіть додатне число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return value;
}

// Введення невід'ємного числа
double readNonNegativeDouble()
{
    double value;

    while (!(cin >> value) || value < 0)
    {
        cout << "Помилка! Введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return value;
}

// Введення тексту з пробілами
string readText()
{
    string text;

    getline(cin >> ws, text);

    while (text.empty())
    {
        cout << "Поле не може бути порожнім. Введіть текст: ";
        getline(cin, text);
    }

    return text;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    FinanceManager manager;

    int choice;

    do
    {
        cout << "\n========== ОСОБИСТІ ФІНАНСИ ==========" << endl;
        cout << "1. Переглянути рахунки" << endl;
        cout << "2. Додати гаманець" << endl;
        cout << "3. Додати дебетову картку" << endl;
        cout << "4. Додати кредитну картку" << endl;
        cout << "5. Поповнити рахунок" << endl;
        cout << "6. Додати витрату" << endl;
        cout << "7. Історія операцій" << endl;
        cout << "8. Звіт за день, тиждень або місяць" << endl;
        cout << "9. Топ-3 найбільших витрат" << endl;
        cout << "10. Топ-3 категорій витрат" << endl;
        cout << "11. Зберегти звіт у файл" << endl;
        cout << "12. Звіт за категоріями" << endl;
        cout << "0. Вихід" << endl;
        cout << "======================================" << endl;

        cout << "Ваш вибір: ";
        choice = readInt();

        string name;
        string number;
        string category;

        double balance;
        double amount;
        double limit;

        int index;
        int period;

        switch (choice)
        {
        case 1:
            manager.showAccounts();
            break;

        case 2:
            cout << "Назва гаманця: ";
            name = readText();

            cout << "Початковий баланс: ";
            balance = readNonNegativeDouble();

            manager.addWallet(name, balance);

            cout << "Гаманець додано!" << endl;
            break;

        case 3:
            cout << "Назва картки: ";
            name = readText();

            cout << "Номер картки: ";
            number = readText();

            cout << "Початковий баланс: ";
            balance = readNonNegativeDouble();

            manager.addDebitCard(name, number, balance);

            cout << "Дебетову картку додано!" << endl;
            break;

        case 4:
            cout << "Назва картки: ";
            name = readText();

            cout << "Номер картки: ";
            number = readText();

            cout << "Початковий баланс: ";
            balance = readNonNegativeDouble();

            cout << "Кредитний ліміт: ";
            limit = readNonNegativeDouble();

            manager.addCreditCard(name, number, balance, limit);

            cout << "Кредитну картку додано!" << endl;
            break;

        case 5:
            manager.showAccounts();

            cout << "Номер рахунку: ";
            index = readInt();

            cout << "Сума поповнення: ";
            amount = readDouble();

            manager.depositMoney(index - 1, amount);
            break;

        case 6:
            manager.showAccounts();

            cout << "Номер рахунку: ";
            index = readInt();

            cout << "Категорія витрати: ";
            category = readText();

            cout << "Сума витрати: ";
            amount = readDouble();

            manager.addExpense(index - 1, amount, category);
            break;

        case 7:
            manager.showTransactions();
            break;

        case 8:
            cout << "\n1. За день" << endl;
            cout << "2. За тиждень" << endl;
            cout << "3. За місяць" << endl;

            cout << "Ваш вибір: ";
            period = readInt();

            if (period >= 1 && period <= 3)
                manager.showReport(period);
            else
                cout << "Неправильний вибір!" << endl;

            break;

        case 9:
            cout << "\n1. За тиждень" << endl;
            cout << "2. За місяць" << endl;

            cout << "Ваш вибір: ";
            period = readInt();

            if (period == 1 || period == 2)
                manager.showTopExpenses(period);
            else
                cout << "Неправильний вибір!" << endl;

            break;

        case 10:
            cout << "\n1. За тиждень" << endl;
            cout << "2. За місяць" << endl;

            cout << "Ваш вибір: ";
            period = readInt();

            if (period == 1 || period == 2)
                manager.showTopCategories(period);
            else
                cout << "Неправильний вибір!" << endl;

            break;

        case 11:
            manager.saveReportToFile();
            break;
        
        case 12:
            cout << "\n1. За день" << endl;
            cout << "2. За тиждень" << endl;
            cout << "3. За місяць" << endl;

            cout << "Ваш вибір: ";
            period = readInt();

            if (period >= 1 && period <= 3)
                manager.showCategoryReport(period);
            else
                cout << "Неправильний вибір!" << endl;

            break;

        case 0:
            cout << "Дякую за використання програми!" << endl;
            break;

        default:
            cout << "Неправильний пункт меню!" << endl;
        }

    } while (choice != 0);

    return 0;
}
