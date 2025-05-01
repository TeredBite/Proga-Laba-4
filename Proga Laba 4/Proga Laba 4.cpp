#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

struct Invoice
{
    string Seller;
    string Buyer;
    double Amount;
    unsigned int Year;
    unsigned int Month;
    unsigned int Day;
};

vector<Invoice> ReadFromFile(char* filename, int n)
{
    vector<Invoice> Records;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл. " << filename << endl;
        return Records;
    }

    for (int i = 0; i < n; i++)
    {
        Invoice inv;
        getline(file, inv.Seller);
        getline(file, inv.Buyer);
        file >> inv.Amount;
        file >> inv.Year >> inv.Month >> inv.Day;
        file.ignore();
        Records.push_back(inv);
    }
    return Records;
}

void PrintVectors(const vector<Invoice>& Records)
{
    int n;
    cout << "Введите количество записей для вывода:";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n && i < (int)Records.size(); i++)
    {
        cout << Records[i].Seller << endl;
        cout << Records[i].Buyer << endl;
        cout << Records[i].Amount << endl;
        cout << Records[i].Year << "-" << Records[i].Month << "-" << Records[i].Day << endl;
    }
}

void AddStart(vector<Invoice>& Records)
{
    int n;
    cout << "Введите число элементов :";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        Invoice inv;
        cout << "Введите продавца: ";
        getline(cin, inv.Seller);
        cout << "Введите покупателя: ";
        getline(cin, inv.Buyer);
        cout << "Введите сумму: ";
        cin >> inv.Amount;
        cout << "Введите дату (Год Месяц День через пробел): ";
        cin >> inv.Year >> inv.Month >> inv.Day;
        cin.ignore();
        Records.insert(Records.begin(), inv);
    }
}

void AddEnd(vector<Invoice>& Records)
{
    int n;
    cout << "Введите число элементов :";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        Invoice inv;
        cout << "Введите продавца: ";
        getline(cin, inv.Seller);
        cout << "Введите покупателя: ";
        getline(cin, inv.Buyer);
        cout << "Введите сумму: ";
        cin >> inv.Amount;
        cout << "Введите дату (Год Месяц День через пробел): ";
        cin >> inv.Year >> inv.Month >> inv.Day;
        cin.ignore();
        Records.insert(Records.end(), inv);
    }
}

void PrintInvoice(const Invoice& inv)
{
    cout << "Продавец: " << inv.Seller << endl;
    cout << "Покупатель: " << inv.Buyer << endl;
    cout << "Сумма: " << inv.Amount << endl;
    cout << "Дата: " << inv.Year << "-" << inv.Month << "-" << inv.Day << endl;
    cout << "---------------------------" << endl;
}

void Search(vector<Invoice>& Records)
{
    if (Records.empty())
    {
        cout << "Нет записей для поиска." << endl;
        return;
    }

    int choice;
    cout << "Выберите критерий поиска:\n"
        << "1. По продавцу\n"
        << "2. По покупателю\n"
        << "3. По сумме\n"
        << "4. По дате\n"
        << "Введите номер: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
    {
        string seller;
        cout << "Введите имя продавца: ";
        getline(cin, seller);
        for (const auto& inv : Records)
            if (inv.Seller == seller) PrintInvoice(inv);
        break;
    }
    case 2:
    {
        string buyer;
        cout << "Введите имя покупателя: ";
        getline(cin, buyer);
        for (const auto& inv : Records)
            if (inv.Buyer == buyer) PrintInvoice(inv);
        break;
    }
    case 3:
    {
        double amount;
        cout << "Введите сумму: ";
        cin >> amount;
        cin.ignore();
        for (const auto& inv : Records)
            if (fabs(inv.Amount - amount) < 1e-6) PrintInvoice(inv);
        break;
    }
    case 4:
    {
        unsigned int year, month, day;
        cout << "Введите дату (Год Месяц День): ";
        cin >> year >> month >> day;
        cin.ignore();
        for (const auto& inv : Records)
            if (inv.Year == year && inv.Month == month && inv.Day == day) PrintInvoice(inv);
        break;
    }
    default:
        cout << "Неверный выбор." << endl;
    }
}

void Sort(vector<Invoice>& Records) {
    int n = Records.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (Records[j].Buyer > Records[j + 1].Buyer) {
                swap(Records[j], Records[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


void PrintWithdrawals(const vector<Invoice>& Records) {
    string seller;
    unsigned int y, m, d;
    cout << "Введите имя продавца (расчетного счета): ";
    getline(cin, seller);
    cout << "Введите дату-предел (Год Месяц День): ";
    cin >> y >> m >> d;
    cin.ignore();
    for (const auto& inv : Records) {
        if (inv.Seller == seller) {
            if ((inv.Year < y) || (inv.Year == y && inv.Month < m) ||
                (inv.Year == y && inv.Month == m && inv.Day < d)) {
                PrintInvoice(inv);
            }
        }
    }
}


void RemoveWithdrawals(vector<Invoice>& Records) {
    string seller;
    unsigned int y, m, d;
    cout << "Введите имя продавца (для удаления): ";
    getline(cin, seller);
    cout << "Введите дату-предел (Год Месяц День): ";
    cin >> y >> m >> d;
    cin.ignore();
    Records.erase(
        remove_if(Records.begin(), Records.end(), [&](const Invoice& inv) {
            if (inv.Seller != seller) return false;
            return (inv.Year < y) || (inv.Year == y && inv.Month < m) ||
                (inv.Year == y && inv.Month == m && inv.Day < d);
            }),
        Records.end()
    );
}


void MergeContainers(vector<Invoice>& Records) {
    vector<Invoice> other;
    char choice;
    cout << "Чтение второго контейнера из файла (f) или консоли (c)? ";
    cin >> choice; cin.ignore();
    int n;
    if (choice == 'f') {
        char fname[256];
        cout << "Введите имя файла: "; cin.getline(fname, 256);
        cout << "Сколько записей читать: "; cin >> n; cin.ignore();
        other = ReadFromFile(fname, n);
    }
    else {
        cout << "Сколько записей вводить: "; cin >> n; cin.ignore();
        for (int i = 0; i < n; i++) {
            Invoice inv;
            cout << "Введите продавца: "; getline(cin, inv.Seller);
            cout << "Введите покупателя: "; getline(cin, inv.Buyer);
            cout << "Введите сумму: "; cin >> inv.Amount;
            cout << "Введите дату (Год Месяц День): "; cin >> inv.Year >> inv.Month >> inv.Day;
            cin.ignore();
            other.push_back(inv);
        }
    }
    cout << "Добавить в начало (h) или конец (e) первого контейнера? ";
    cin >> choice; cin.ignore();
    if (choice == 'h') Records.insert(Records.begin(), other.begin(), other.end());
    else Records.insert(Records.end(), other.begin(), other.end());
}


void OutputContainer(const vector<Invoice>& Records) {
    char choice;
    cout << "Вывести в консоль (c) или в файл (f)? ";
    cin >> choice; cin.ignore();
    if (choice == 'f') {
        char fname[256];
        cout << "Введите имя файла: ";
        cin.getline(fname, 256);
        ofstream ofile(fname);
        for (const auto& inv : Records) {
            ofile << inv.Seller << endl;
            ofile << inv.Buyer << endl;
            ofile << inv.Amount << endl;
            ofile << inv.Year << " " << inv.Month << " " << inv.Day << endl;
        }
    }
    else {
        for (const auto& inv : Records) PrintInvoice(inv);
    }
}

int main()
{
    vector<Invoice> Records;
    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Читать из файла\n"
            << "2. Добавить в начало\n"
            << "3. Добавить в конец\n"
            << "4. Поиск\n"
            << "5. Сортировка по покупателю\n"
            << "6. Вывод всех записей\n"
            << "7. Вывести снятия по продавцу до даты\n"
            << "8. Удалить снятия по продавцу до даты\n"
            << "9. Слияние с другим контейнером\n"
            << "10. Вывести контейнер\n"
            << "11. Выход\n"
            << "Ваш выбор: ";
        cin >> choice; cin.ignore();
        switch (choice) {
        case 1: {
            char fname[256]; int n;
            cout << "Введите имя файла: "; getline(cin, fname);
            cout << "Сколько записей читать: "; cin >> n; cin.ignore();
            Records = ReadFromFile(fname, n);
            break;
        }
        case 2: AddStart(Records); break;
        case 3: AddEnd(Records); break;
        case 4: Search(Records); break;
        case 5: Sort(Records); break;
        case 6: PrintVectors(Records); break;
        case 7: PrintWithdrawals(Records); break;
        case 8: RemoveWithdrawals(Records); break;
        case 9: MergeContainers(Records); break;
        case 10: OutputContainer(Records); break;
        case 11: cout << "Выход..." << endl; break;
        default: cout << "Неверный выбор." << endl;
        }
    } while (choice != 11);
    return 0;
}