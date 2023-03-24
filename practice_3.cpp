#include <iostream>
#include <windows.h>
#include <string.h>
#include <iomanip>

using namespace std;

struct Date
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct Record
{
    char surname[20];
    char code;
    float count;
    unsigned short place;
    struct Date date;
};

struct Node {
    Record data;
    Node* pnext;
    Node* pprev;
};

Node* head = NULL; Node* tail = NULL;
int cnt_of_items = 0;

/// <summary>
/// Добавление элемента в начало
/// </summary>
/// <param name="data"></param>
void insert_at_head(Record data) {
    Node* pnew = new Node;
    pnew->data = data;
    pnew->pnext = head;
    if (cnt_of_items == 0)
        pnew->pnext = pnew->pprev = NULL;
    else
        pnew->pprev = pnew;
    head = pnew;
    cnt_of_items++;
    cout << "blaaa" << endl;
}

/// <summary>
/// Добавление элемента в конец
/// </summary>
/// <param name="data"></param>
void insert_at_tail(Record data) {
    Node* pnew = new Node;
    pnew->data = data;
    if (cnt_of_items == 0)
        insert_at_head(data);
    else
        pnew->pprev = tail;
    tail = pnew;
    cnt_of_items++;
}

/// <summary>
/// Добавление элемента по индексу
/// </summary>
/// <param name="idx"></param>
/// <param name="data"></param>
void insert_by_index(int idx, Record data) {
    if (not(idx >= 0 and idx <= cnt_of_items and cnt_of_items >= 0))
        insert_at_head(data);
    else{
        idx = 0;
        Node* pcur = head;
        for (int i = 0; i < idx - 1; i++)
            pcur = pcur->pnext;
        Node* paft = pcur->pnext;
        Node* pnew = new Node;
        pnew->pnext = paft; paft->pprev = pnew;
        pcur->pnext = pnew; pnew->pprev = pcur;
        cnt_of_items++;
    }
}



void myCentr(string s, int wLine) {

    unsigned short w = s.length();
    int delta = (wLine - w) / 2;
    cout << left;
    cout.width(delta); cout << " ";
    cout << s;
    cout.width(delta + 1); cout << " ";
}


void Printdate(unsigned short day, unsigned short month, unsigned short year, int wLine)
{
    int w = 10;
    int delta = (wLine - w) / 2 - 1;
    cout << left;
    cout.width(delta); cout << " ";
    if (day > 9) {
        cout << day;
    }
    else {
        cout << "0" << day;
    }
    cout << ".";
    if (month > 9) {
        cout << month;
    }
    else {
        cout << "0" << month;
    }
    cout << ".";
    cout << year;
    cout.width(delta);
    cout << " ";
}

void border(int width) {
    cout.width(width); cout.fill('-'); cout << "-" << endl;
}

void Table(struct Record* records)
{
    int width = 80;
    int datespace = 9;
    cout << endl; border(width + 1);
    cout.width(width); cout.fill(' '); cout << left << "|Ведомость спортивных состязаний"; cout << "|" << endl;
    border(width + 1);
    cout.fill(' ');
    cout << left << "|Фамилия участника";
    cout << left << "|Код команды";
    cout << left << "|Количество балов";
    cout << left << "|Место в итоге";
    cout << "|";  myCentr("Дата выступления", 12); cout << "|" << endl;
    cout.fill(' ');
    border(width + 1);
    cout.fill(' ');
    for (int i = 0; i < 3; i++) {
        cout << left << "|"; cout.width(17); cout << left << records[i].surname;
        cout << left << "|"; cout.width(11); cout << left << records[i].code;
        cout << left << "|"; cout.width(16); cout << left << records[i].count;
        cout << left << "|"; cout.width(13); cout << left << records[i].place;
        cout << left << "|";
        Printdate(records[i].date.day, records[i].date.month, records[i].date.year, 20);
        cout << "|" << endl;
    }
    border(width + 1);
    cout.fill(' '); cout.width(width - 1); cout << left << "| Примечание: Д - \"Динамо\", С - \"Спартак\", Ш - \"Шахтер\""; cout << " | " << endl;
    border(width + 1);
}

void Input(struct Record* records) {
    for (int i = 0; i < 3; i++) {
        cout << "Input the " << i + 1 << " line" << endl << endl;
        cout << i + 1 << " participant's surname:"; cin >> records[i].surname;
        cout << i + 1 << " code of team:"; cin >> records[i].code;
        cout << i + 1 << " count of points:"; cin >> records[i].count;
        cout << i + 1 << " place in the end:"; cin >> records[i].place;
        cout << i + 1 << " performance date:"; cin >> records[i].date.day >> records[i].date.month >> records[i].date.year; cout << endl;
    }
}
/// <summary>
/// Печать списка
/// </summary>
void print_table() {
    Node* pcur = head;
    int width = 80;
    int datespace = 9;
    cout << endl; border(width + 1);
    cout.width(width); cout.fill(' '); cout << left << "|Ведомость спортивных состязаний"; cout << "|" << endl;
    border(width + 1);
    cout.fill(' ');
    cout << left << "|Фамилия участника";
    cout << left << "|Код команды";
    cout << left << "|Количество балов";
    cout << left << "|Место в итоге";
    cout << "|";  myCentr("Дата выступления", 12); cout << "|" << endl;
    cout.fill(' ');
    border(width + 1);
    cout.fill(' ');
    for (int i = 0; i < cnt_of_items; i++) {
        cout << left << "|"; cout.width(17); cout << left << pcur->data.surname;
        cout << left << "|"; cout.width(11); cout << left << pcur->data.code;
        cout << left << "|"; cout.width(16); cout << left << pcur->data.count;
        cout << left << "|"; cout.width(13); cout << left << pcur->data.place;
        cout << left << "|";
        Printdate(pcur->data.date.day, pcur->data.date.month, pcur->data.date.year, 20);
        cout << "|" << endl;
        pcur = pcur->pnext;
    }
    border(width + 1);
    cout.fill(' '); cout.width(width - 1); cout << left << "| Примечание: Д - \"Динамо\", С - \"Спартак\", Ш - \"Шахтер\""; cout << " | " << endl;
    border(width + 1);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct Record records[5];

     records[0] = { "Баландин", 'С', 123.7000, 2, {6,6,2022} };
     records[1] = { "Шишков", 'Ш', 79.9800, 3, {7,7,2022}};
     records[2] = { "Кравченко", 'Д', 134.8000, 1, {7,6,2022}};

     for (int i = 0; i < 2; i++)
         for (int j = 0; j < 3; j++)
             insert_at_head(records[j]);
     print_table();
    /*Input(records);


    Table(records);*/
}