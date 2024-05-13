//  Создать класс СПРАВОЧНИК со следующими полями:
//  1. Название фирмы;
//  2. Владелец;
//  3. Телефон;
//  4. Адрес;
//  5. Род деятельности.
//  Реализовать следующие возможности :
//  1. Поиск по названию;
//  2. Поиск по владельцу;
//  3. Поиск по номеру телефона;
//  4. Поиск по роду деятельности;
//  5. Показ всех записей и добавление.
//  Вся информация, должна сохранятся в файле, должна
//  быть реализована возможность добавления новых данных.


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Handbook {
private:
    string companyName;
    string owner;
    string phoneNumber;
    string address;
    string activityType;

public:
    Handbook() {}

    void addEntry() {   //  Добавляем новую запись
        ofstream file("handbook.txt", ios_base::app); // Открываем файл для добавления

        cout << "Enter company name: ";
        getline(cin, companyName);

        cout << "Enter owner: ";
        getline(cin, owner);

        cout << "Enter phone number: ";
        getline(cin, phoneNumber);

        cout << "Enter address: ";
        getline(cin, address);

        cout << "Enter type of activity: ";
        getline(cin, activityType);

        // Записываем данные в файл
        file << companyName << " | " << owner << " | " << phoneNumber << " | " << address << " | " << activityType << endl;

        file.close();
    }

    void searchByName(const string& name) { //  Поиск по названию фирмы
        ifstream file("handbook.txt");

        string line;
        while (getline(file, line)) {
            if (line.find(name) != string::npos) {
                cout << line << endl;
            }
        }

        file.close();
    }

    void searchByOwner(const string& ownerName) {   //  Поиск по владельцу
        ifstream file("handbook.txt");

        string line;
        while (getline(file, line)) {
            if (line.find(ownerName) != string::npos) {
                cout << line << endl;
            }
        }

        file.close();
    }

    void searchByPhoneNumber(const string& phone) { //  Поиск по номеру
        ifstream file("handbook.txt");

        string line;
        while (getline(file, line)) {
            if (line.find(phone) != string::npos) {
                cout << line << endl;
            }
        }

        file.close();
    }

    void searchByActivity(const string& activity) { //  Поиск по роду деятельности
        ifstream file("handbook.txt");

        string line;
        while (getline(file, line)) {
            if (line.find(activity) != string::npos) {
                cout << line << endl;
            }
        }

        file.close();
    }

    void showAllEntries() { //  Показать все записи
        ifstream file("handbook.txt");

        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

int main() {
    Handbook handbook;
    int option;
    string input;

    do {
        cout << "1. Add new entry" << endl;
        cout << "2. Search by name" << endl;
        cout << "3. Search by owner" << endl;
        cout << "4. Search by phone number" << endl;
        cout << "5. Search by type of activity" << endl;
        cout << "6. Show all entries" << endl;
        cout << "0. Exit" << endl;

        cin >> option;
        cin.ignore(); // Очищаем буфер ввода

        switch (option) {
        case 1:
            handbook.addEntry();
            break;
        case 2:
            cout << "Enter name to search: ";
            getline(cin, input);
            handbook.searchByName(input);
            break;
        case 3:
            cout << "Enter owner to search: ";
            getline(cin, input);
            handbook.searchByOwner(input);
            break;
        case 4:
            cout << "Enter phone number to search: ";
            getline(cin, input);
            handbook.searchByPhoneNumber(input);
            break;
        case 5:
            cout << "Enter type of activity to search: ";
            getline(cin, input);
            handbook.searchByActivity(input);
            break;
        case 6:
            handbook.showAllEntries();
            break;
        case 0:
            cout << "Exiting...";
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 0);

    return 0;
}