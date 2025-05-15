#include <iostream>
#include <string>
#include <set>
#include <map>
#include <limits>
#include <cmath>


using namespace std;


static const double PI = acos(-1.0);

// Регулярный многоугольник
struct Polygon {
    int sides;
    double length;
    double area() const { return sides * length * length / (4 * tan(PI / sides)); }
    double perimeter() const { return sides * length; }
};

// Структура для книги
struct Book {
    string author;
    int year;
    int copies;
};

// Ввод целого числа
int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка, попробуйте снова." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

// Ввод вещественного числа
double readDouble(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка, попробуйте снова." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

// Задача 1: multiset полигонов
void task1() {
    cout << "Выберите сортировку:\n"
        "1 - по возрастанию площади\n"
        "2 - по убыванию площади\n";
    int choice = readInt("Ваш выбор: ");

    // Лямбда-компараторы
    auto cmpAsc = [](const Polygon& a, const Polygon& b) { return a.area() < b.area(); };
    auto cmpDesc = [](const Polygon& a, const Polygon& b) { return a.area() > b.area(); };

    if (choice == 1) {
        multiset<Polygon, decltype(cmpAsc)> ms(cmpAsc);
        int count = readInt("Сколько полигонов ввести? ");
        for (int i = 0; i < count; ++i) {
            int sides = readInt("Количество сторон: ");
            double len = readDouble("Длина стороны: ");
            if (sides < 3 || len <= 0) cout << "Неверные параметры, пропуск." << endl;
            else ms.insert({ sides, len });
        }
        cout << "Результат (площадь, периметр):\n";
        for (const auto& p : ms) cout << p.area() << ", " << p.perimeter() << endl;
    }
    else {
        multiset<Polygon, decltype(cmpDesc)> ms(cmpDesc);
        int count = readInt("Сколько полигонов ввести? ");
        for (int i = 0; i < count; ++i) {
            int sides = readInt("Количество сторон: ");
            double len = readDouble("Длина стороны: ");
            if (sides < 3 || len <= 0) cout << "Неверные параметры, пропуск." << endl;
            else ms.insert({ sides, len });
        }
        cout << "Результат (площадь, периметр):\n";
        for (const auto& p : ms) cout << p.area() << ", " << p.perimeter() << endl;
    }
}

// Задача 2: map библиотеки
void task2() {
    map<string, Book> library;
    int count = readInt("Сколько книг добавить? ");
    string title;
    getline(cin, title); // очистка
    for (int i = 0; i < count; ++i) {
        cout << "Название книги: ";
        getline(cin, title);
        Book b;
        cout << "Автор: ";
        getline(cin, b.author);
        b.year = readInt("Год издания: ");
        b.copies = readInt("Число экземпляров: ");
        library[title] = b;
    }
    cout << "Содержимое библиотеки:\n";
    for (auto it = library.begin(); it != library.end(); ++it) {
        cout << it->first << " | "
            << it->second.author << " | "
            << it->second.year << " | "
            << it->second.copies << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        cout << "\nМеню:\n"
            "1 - Задача 1 (мультисет полигонов)\n"
            "2 - Задача 2 (карта книг)\n"
            "3 - Выход\n";
        int option = readInt("Выберите пункт: ");
        if (option == 1) task1();
        else if (option == 2) task2();
        else if (option == 3) break;
        else cout << "Неверный выбор, попробуйте снова." << endl;
    }
    return 0;
}
