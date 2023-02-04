#include<iostream>
using namespace std;

const int MAX_SIZE = 100;

struct Employee {
    string name;
    int day;
    int month;
    int year;
};

int hashFunction(int day, int month, int limit) {
    return (day * month - 1) % limit;
}

int main() {
    int tableSize, numEmployees, day, month;
    Employee employees[MAX_SIZE];
    int count[MAX_SIZE];

    cin >> tableSize >> numEmployees;

    for (int i = 0; i < numEmployees; i++) {
        cin >> employees[i].name >> employees[i].day >> employees[i].month >> employees[i].year;
    }

    cin >> day >> month;

    for (int i = 0; i < tableSize; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < numEmployees; i++) {
        int index = hashFunction(employees[i].day, employees[i].month, tableSize);
        count[index]++;
    }

    int birthdayCount = count[hashFunction(day, month, tableSize)];
    cout << birthdayCount << endl;

    double percentage = (double) birthdayCount / numEmployees;
    cout << percentage << endl;

    return 0;
}

